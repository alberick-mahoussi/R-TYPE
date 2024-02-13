/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEMCLIENT_HPP_
#define COLLISIONSYSTEMCLIENT_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"
#include <vector>
#include <map>

class CustomGrid {
    public:
        CustomGrid() {
            grid.resize(10, std::vector<std::map<TeamType, std::vector<int>>>(10));
        };
        ~CustomGrid() {
            grid.clear();
            grid.shrink_to_fit();
        }
        void setValue(int x, int y, TeamType team, int value) {
            grid[x][y][team].push_back(value);
        };
        std::vector<int> getValues(int x, int y, TeamType team) {
            return grid[x][y][team];
        };
    private:
        std::vector<std::vector<std::map<TeamType, std::vector<int>>>> grid;
};

class CollisionSystemClient : public System {
    public:
        CollisionSystemClient(Registry &registry) : _registry(registry) {};
        ~CollisionSystemClient();
        bool checkCollision(std::optional<PositionComponent> const allyHitbox, std::optional<PositionComponent> const enemyHitbox,
        std::optional<ScaleComponent> const allyScale, std::optional<ScaleComponent> const enemyScale) {
            bool xOverlap = (allyHitbox->_x + 5 < enemyHitbox->_x + (enemyHitbox->_wth * enemyScale->_scaleX) - 5 ) && (allyHitbox->_x + (allyHitbox->_wth * allyScale->_scaleX) - 5 > enemyHitbox->_x + 5 );
            bool yOverlap = (allyHitbox->_y < enemyHitbox->_y + (enemyHitbox->_hgt * enemyScale->_scaleY)) && (allyHitbox->_y + (allyHitbox->_hgt * allyScale->_scaleY) > enemyHitbox->_y);
            return (xOverlap && yOverlap);
        }
        void callSystem() {
            auto const &TeamComp = _registry.get_components<TeamComponent>();
            auto const &PositionComp = _registry.get_components<PositionComponent>();
            auto &entityComp = _registry.get_components<DeadComponent>();
            auto &ScaleComp = _registry.get_components<ScaleComponent>();
            auto &DamageComp = _registry.get_components<DamageComponent>();
            auto &HealthComp = _registry.get_components<HealthComponent>();
            auto &ScoreComp = _registry.get_components<ScoreComponent>();
            auto &SoundComp = _registry.get_components<SoundComponent>();
            auto &DestroyedComp = _registry.get_components<DestroyedComponent>();
            auto &ShootableComp = _registry.get_components<ShootableComponent>();

            CustomGrid grid;

            for (size_t i = 0; i < TeamComp.size(); i++) {
                auto const &Team = TeamComp[i];
                auto const &Position = PositionComp[i];
                auto const &scale = ScaleComp[i];

                if (Team && Position && scale && (Team->_team == TeamType::ALLY || Team->_team == TeamType::ENEMY)) {
                    int cellXStart = static_cast<int>(Position->_x/ cellWidth);
                    int cellYStart = static_cast<int>(Position->_y/ cellHeight);
                    int cellXEnd = static_cast<int>((Position->_x + Position->_wth * scale->_scaleY) / cellWidth);
                    int cellYEnd = static_cast<int>((Position->_y + Position->_hgt * scale->_scaleY) / cellHeight);

                    cellXStart = std::max(0, std::min(cellXStart, cellCountX - 1));
                    cellYStart = std::max(0, std::min(cellYStart, cellCountY - 1));
                    cellXEnd = std::max(0, std::min(cellXEnd, cellCountX - 1));
                    cellYEnd = std::max(0, std::min(cellYEnd, cellCountY - 1));

                    for (int cellX = cellXStart; cellX <= cellXEnd; cellX++) {
                        for (int cellY = cellYStart; cellY <= cellYEnd; cellY++) {
                            grid.setValue(cellX, cellY, Team->_team, i);
                        }
                    }
                }
            }
            for (size_t y = 0; y < cellCountY; ++y) {
                for (size_t x = 0; x < cellCountX; ++x) {
                    const std::vector<int>& allyEntities = grid.getValues(x, y, TeamType::ALLY);
                    const std::vector<int>& enemyEntities = grid.getValues(x, y, TeamType::ENEMY);
                    for (int allyIndex : allyEntities) {
                        for (int enemyIndex : enemyEntities) {
                            auto const &allyHitbox = PositionComp[allyIndex];
                            auto const &enemyHitbox = PositionComp[enemyIndex];
                            auto &entity = entityComp[allyIndex];
                            auto &scale = ScaleComp[allyIndex];
                            auto &entity2 = entityComp[enemyIndex];
                            auto &scale2 = ScaleComp[enemyIndex];
                            auto &damage = DamageComp[allyIndex];
                            auto &health = HealthComp[damage->_playerId];
                            auto &damage2 = DamageComp[enemyIndex];
                            auto &health2 = HealthComp[damage2->_playerId];
                            auto &score = ScoreComp[damage->_playerId];
                            auto &sound = SoundComp[damage->_playerId];
                            auto &shoot = ShootableComp[damage->_playerId];
                            auto &shoot2 = ShootableComp[damage2->_playerId];
                            auto &sound2 = SoundComp[damage2->_playerId];
                            auto &destroy = DestroyedComp[damage->_playerId];
                            auto &destroy2 = DestroyedComp[damage2->_playerId];
                            if (entity && entity2 && (entity->_alive == false && entity2->_alive == false)) {
                                if (checkCollision(allyHitbox, enemyHitbox, scale, scale2)) {
                                    if (entity->_entityType == EntityType::BULLET && entity2->_entityType != EntityType::ITEM && entity2->_entityType != EntityType::BULLET) {
                                        entity->_alive = true;
                                    }
                                    if (entity2->_entityType == EntityType::ITEM) {
                                        if (entity->_entityType == EntityType::PLAYER) {
                                            entity2->_alive = true;
                                            damage->_bonus += 10;
                                            damage->_damage += 10;
                                            score->_score += 100;
                                        }
                                    }
                                    if (entity2->_entityType == EntityType::MOB) {
                                        if (entity->_entityType == EntityType::PLAYER) {
                                            health2->_current_health = 0;
                                        } else
                                            health2->_current_health -= damage->_damage;
                                        if (health2->_current_health <= 0) {
                                            entity2->_alive = true;
                                            destroy2->_isDestroy = true;
                                            sound2->_index = 1;
                                            shoot2->_shoot = false;
                                            if (entity->_entityType != EntityType::PLAYER)
                                                score->_score += 100;
                                        }
                                    }
                                    if (entity->_entityType == EntityType::PLAYER) {
                                        if (entity2->_entityType == EntityType::BULLET) {
                                            entity2->_alive = true;
                                        }
                                        if (health->_current_health <= 0) {
                                            entity->_alive = true;
                                            sound->_index = 2;
                                            destroy->_isDestroy = true;
                                            shoot->_shoot = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }

    protected:
    private:
        Registry &_registry;
        const int cellCountX = 10;
        const int cellCountY = 10;
        const float cellWidth = 192.0f;
        const float cellHeight = 108.0f;
};

#endif /* !COLLISIONSYSTEM_HPP_ */
