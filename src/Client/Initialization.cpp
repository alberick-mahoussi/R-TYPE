/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** Initialization
*/

#include "Client/Client.hpp"


void Client::initGame()
{
    std::vector<std::string> scenes = {"Play"};

    auto backgrounGame = _registry.spawn_entity();

    _registry.add_component<PositionComponent>(backgrounGame, PositionComponent{0, 0, 1920, 1080});
    _registry.add_component<DrawableComponent>(backgrounGame, DrawableComponent{true});
    _registry.add_component<TextureComponent>(backgrounGame, TextureComponent{BACKGROUND_GAME, true});
    _registry.add_component<SceneComponent>(backgrounGame, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(backgrounGame, SpriteInitializedComponent{false});

    auto score = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(score, PositionComponent{120, 980.0f, 0, 0});
    _registry.add_component<DrawableComponent>(score, DrawableComponent{false});
    _registry.add_component<TextComponent>(score, TextComponent{"score: ", "white", 40});
    _registry.add_component<SceneComponent>(score, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(score, SpriteInitializedComponent{false});
    _registry.add_component<GuiComponent>(score, GuiComponent{"Score"});

    auto attack = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(attack, PositionComponent{800.0f, 980.0f, 0, 0});
    _registry.add_component<DrawableComponent>(attack, DrawableComponent{false});
    _registry.add_component<TextComponent>(attack, TextComponent{"attack: ", "white", 40});
    _registry.add_component<SceneComponent>(attack, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(attack, SpriteInitializedComponent{false});
    _registry.add_component<GuiComponent>(attack, GuiComponent{"Attack"});

    auto health = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(health, PositionComponent{1500.0f, 980.0f, 0, 0});
    _registry.add_component<DrawableComponent>(health, DrawableComponent{false});
    _registry.add_component<TextComponent>(health, TextComponent{"health: ", "white", 40});
    _registry.add_component<SceneComponent>(health, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(health, SpriteInitializedComponent{false});
    _registry.add_component<GuiComponent>(health, GuiComponent{"Health"});

    auto blankEntity = 0;
    while (blankEntity != 60) {
        blankEntity = _registry.spawn_entity();
    }
}

void Client::initLoggingScreen()
{
    int fontSize = 40;
    double posLeft = 600.f;
    double posRight = 1150.f;
    std::vector<std::string> scenes = {"LoginScreen"};

    auto username = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(username, PositionComponent{posLeft, 300.0f, 0, 0});
    _registry.add_component<DrawableComponent>(username, DrawableComponent{false});
    _registry.add_component<TextComponent>(username, TextComponent{"Username: ", "white", fontSize});
    _registry.add_component<SceneComponent>(username, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(username, SpriteInitializedComponent{false});

    auto textBox1 = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(textBox1, PositionComponent{posRight, 300.0f, 0, 0});
    _registry.add_component<DrawableComponent>(textBox1, DrawableComponent{true});
    _registry.add_component<TextComponent>(textBox1, TextComponent{"..........", "white", fontSize});
    _registry.add_component<SceneComponent>(textBox1, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(textBox1, SpriteInitializedComponent{false});
    _registry.add_component<TextBoxComponent>(textBox1, TextBoxComponent{1});

    auto ipAdress = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(ipAdress, PositionComponent{posLeft, 450.0f, 0, 0});
    _registry.add_component<DrawableComponent>(ipAdress, DrawableComponent{true});
    _registry.add_component<TextComponent>(ipAdress, TextComponent{"IP adress: ", "white", fontSize});
    _registry.add_component<SceneComponent>(ipAdress, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(ipAdress, SpriteInitializedComponent{false});

    auto textBox2 = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(textBox2, PositionComponent{posRight, 450.0f, 0, 0});
    _registry.add_component<DrawableComponent>(textBox2, DrawableComponent{true});
    _registry.add_component<TextComponent>(textBox2, TextComponent{"..........", "white", fontSize});
    _registry.add_component<TextBoxComponent>(textBox2, TextBoxComponent{2});
    _registry.add_component<SceneComponent>(textBox2, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(textBox2, SpriteInitializedComponent{false});

    auto port = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(port, PositionComponent{posLeft, 600.0f, 0, 0});
    _registry.add_component<DrawableComponent>(port, DrawableComponent{false});
    _registry.add_component<TextComponent>(port, TextComponent{"Port: ", "white", fontSize});
    _registry.add_component<SceneComponent>(port, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(port, SpriteInitializedComponent{false});

    auto textBox3 = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(textBox3, PositionComponent{posRight, 600.0f, 0, 0});
    _registry.add_component<DrawableComponent>(textBox3, DrawableComponent{true});
    _registry.add_component<TextComponent>(textBox3, TextComponent{"..........", "white", fontSize});
    _registry.add_component<TextBoxComponent>(textBox3, TextBoxComponent{3});
    _registry.add_component<SceneComponent>(textBox3, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(textBox3, SpriteInitializedComponent{false});

    auto readyBtn = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(readyBtn, PositionComponent{1280.0f, 860.0f, 0, 0});
    _registry.add_component<DrawableComponent>(readyBtn, DrawableComponent{true});
    _registry.add_component<TextComponent>(readyBtn, TextComponent{"Press Enter to confirm", "white", fontSize});
    _registry.add_component<SceneComponent>(readyBtn, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(readyBtn, SpriteInitializedComponent{false});

    auto exitBtn = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(exitBtn, PositionComponent{250.0f, 860.0f, 0, 0});
    _registry.add_component<DrawableComponent>(exitBtn, DrawableComponent{true});
    _registry.add_component<TextComponent>(exitBtn, TextComponent{"Press Escape to exit", "white", fontSize});
    _registry.add_component<SceneComponent>(exitBtn, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(exitBtn, SpriteInitializedComponent{false});
}

void Client::initWaitingRoom()
{
    int fontSize = 40;
    double posLeft = 500.f;
    double posRight = 1260.f;
    std::vector<std::string> scenes = {"LoginScreen", "WaitingScreen"};

    auto background = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(background, PositionComponent{0, 0, 0, 0});
    _registry.add_component<DrawableComponent>(background, DrawableComponent{true});
    _registry.add_component<TextureComponent>(background, TextureComponent{WAITING_SCREEN, false});
    _registry.add_component<SceneComponent>(background, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(background, SpriteInitializedComponent{false});

    initLoggingScreen();

    scenes = {"WaitingScreen"};

    auto player1 = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(player1, PositionComponent{posLeft, 300.0f, 0, 0});
    _registry.add_component<DrawableComponent>(player1, DrawableComponent{false});
    _registry.add_component<TextComponent>(player1, TextComponent{"Waiting...", "white", fontSize});
    _registry.add_component<SceneComponent>(player1, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(player1, SpriteInitializedComponent{false});

    auto player2 = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(player2, PositionComponent{posLeft, 400.0f, 0, 0});
    _registry.add_component<DrawableComponent>(player2, DrawableComponent{true});
    _registry.add_component<TextComponent>(player2, TextComponent{"Waiting...", "white", fontSize});
    _registry.add_component<SceneComponent>(player2, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(player2, SpriteInitializedComponent{false});

    auto player3 = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(player3, PositionComponent{posLeft, 500.0f, 0, 0});
    _registry.add_component<DrawableComponent>(player3, DrawableComponent{true});
    _registry.add_component<TextComponent>(player3, TextComponent{"Waiting...", "white", fontSize});
    _registry.add_component<SceneComponent>(player3, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(player3, SpriteInitializedComponent{false});

    auto player4 = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(player4, PositionComponent{posLeft, 600.0f, 0, 0});
    _registry.add_component<DrawableComponent>(player4, DrawableComponent{true});
    _registry.add_component<TextComponent>(player4, TextComponent{"Waiting...", "white", fontSize});
    _registry.add_component<SceneComponent>(player4, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(player4, SpriteInitializedComponent{false});

    auto ready1 = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(ready1, PositionComponent{posRight, 300.0f, 0, 0});
    _registry.add_component<DrawableComponent>(ready1, DrawableComponent{true});
    _registry.add_component<TextComponent>(ready1, TextComponent{"Not ready", "white", fontSize});
    _registry.add_component<SceneComponent>(ready1, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(ready1, SpriteInitializedComponent{false});

    auto ready2 = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(ready2, PositionComponent{posRight, 400.0f, 0, 0});
    _registry.add_component<DrawableComponent>(ready2, DrawableComponent{true});
    _registry.add_component<TextComponent>(ready2, TextComponent{"Not ready", "white", fontSize});
    _registry.add_component<SceneComponent>(ready2, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(ready2, SpriteInitializedComponent{false});

    auto ready3 = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(ready3, PositionComponent{posRight, 500.0f, 0, 0});
    _registry.add_component<DrawableComponent>(ready3, DrawableComponent{true});
    _registry.add_component<TextComponent>(ready3, TextComponent{"Not ready", "white", fontSize});
    _registry.add_component<SceneComponent>(ready3, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(ready3, SpriteInitializedComponent{false});

    auto ready4 = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(ready4, PositionComponent{posRight, 600.0f, 0, 0});
    _registry.add_component<DrawableComponent>(ready4, DrawableComponent{true});
    _registry.add_component<TextComponent>(ready4, TextComponent{"Not ready", "white", fontSize});
    _registry.add_component<SceneComponent>(ready4, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(ready4, SpriteInitializedComponent{false});

    _registry._list.player.push_back(player1);
    _registry._list.player.push_back(player2);
    _registry._list.player.push_back(player3);
    _registry._list.player.push_back(player4);
    _registry._list.ready.push_back(ready1);
    _registry._list.ready.push_back(ready2);
    _registry._list.ready.push_back(ready3);
    _registry._list.ready.push_back(ready4);

    auto readyBtn = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(readyBtn, PositionComponent{1350.0f, 860.0f, 0, 0});
    _registry.add_component<DrawableComponent>(readyBtn, DrawableComponent{true});
    _registry.add_component<TextComponent>(readyBtn, TextComponent{"Press R for ready", "white", fontSize});
    _registry.add_component<SceneComponent>(readyBtn, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(readyBtn, SpriteInitializedComponent{false});

    auto exitBtn = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(exitBtn, PositionComponent{250.0f, 860.0f, 0, 0});
    _registry.add_component<DrawableComponent>(exitBtn, DrawableComponent{true});
    _registry.add_component<TextComponent>(exitBtn, TextComponent{"Press Escape to exit", "white", fontSize});
    _registry.add_component<SceneComponent>(exitBtn, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(exitBtn, SpriteInitializedComponent{false});
}

void Client::initMenu()
{
    std::vector<std::string> scenes = {""};

    auto init = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(0, PositionComponent{0, 0, 0, 0});
    _registry.add_component<VelocityComponent>(0, VelocityComponent{0, 0});
    _registry.add_component<DrawableComponent>(0, DrawableComponent{false});
    _registry.add_component<TextureComponent>(0, TextureComponent{"", false});
    _registry.add_component<SceneComponent>(0, SceneComponent{scenes});
    _registry.add_component<TextComponent>(0, TextComponent{"", "", 0});
    _registry.add_component<ScaleComponent>(0, ScaleComponent{0, 0});
    _registry.add_component<AnimationComponent>(0, AnimationComponent{false, 0, 0, 0, 0, 0, 0});
    _registry.add_component<InputComponent>(0, InputComponent{false});
    _registry.add_component<ShootableComponent>(0, ShootableComponent{false, ShootType::NO_SHOOT, 0});
    _registry.add_component<TeamComponent>(0, TeamComponent{TeamType::NO_TEAM});
    _registry.add_component<DeadComponent>(0, DeadComponent{false, EntityType::VOID});
    _registry.add_component<SpriteInitializedComponent>(0, SpriteInitializedComponent{false});
    _registry.add_component<DamageComponent>(0, DamageComponent{0, 0, 0});
    _registry.add_component<TextBoxComponent>(0, TextBoxComponent{0});
    _registry.add_component<HealthComponent>(0, HealthComponent{0, false});
    _registry.add_component<AIComponent>(0, AIComponent{false});
    _registry.add_component<CollisionComponent>(0, CollisionComponent{false});
    _registry.add_component<SoundComponent>(0, SoundComponent{{}, 0});
    _registry.add_component<WeaponComponent>(0, WeaponComponent{false});
    _registry.add_component<ScoreComponent>(0, ScoreComponent{});
    _registry.add_component<DropableComponent>(0, DropableComponent{false, 0, 0});
    _registry.add_component<GuiComponent>(0, GuiComponent{""});
    _registry.add_component<DestroyedComponent>(0, DestroyedComponent{false, 0});

    scenes = {"Menu"};

    auto background = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(background, PositionComponent{0, 0, 0, 0});
    _registry.add_component<DrawableComponent>(background, DrawableComponent{true});
    _registry.add_component<TextureComponent>(background, TextureComponent{BACKGROUND_MENU, false});
    _registry.add_component<SceneComponent>(background, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(background, SpriteInitializedComponent{false});

    auto tittle = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(tittle, PositionComponent{100.0f, 100.0f, 0, 0});
    _registry.add_component<DrawableComponent>(tittle, DrawableComponent{true});
    _registry.add_component<TextComponent>(tittle, TextComponent{"R-TYPE", "white", 175});
    _registry.add_component<SceneComponent>(tittle, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(tittle, SpriteInitializedComponent{false});

    auto playButton = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(playButton, PositionComponent{175.0f, 500.0f, 0, 0});
    _registry.add_component<DrawableComponent>(playButton, DrawableComponent{true});
    _registry.add_component<TextComponent>(playButton, TextComponent{"PLAY", "white", 60});
    _registry.add_component<SceneComponent>(playButton, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(playButton, SpriteInitializedComponent{false});

    auto settingsButton = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(settingsButton, PositionComponent{175.0f, 625.0f, 0, 0});
    _registry.add_component<DrawableComponent>(settingsButton, DrawableComponent{true});
    _registry.add_component<TextComponent>(settingsButton, TextComponent{"SETTINGS", "white", 60});
    _registry.add_component<SceneComponent>(settingsButton, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(settingsButton, SpriteInitializedComponent{false});

    auto exitButton = _registry.spawn_entity();
    _registry.add_component<PositionComponent>(exitButton, PositionComponent{175.0f, 750.0f, 0, 0});
    _registry.add_component<DrawableComponent>(exitButton, DrawableComponent{true});
    _registry.add_component<TextComponent>(exitButton, TextComponent{"EXIT", "white", 60});
    _registry.add_component<SceneComponent>(exitButton, SceneComponent{scenes});
    _registry.add_component<SpriteInitializedComponent>(exitButton, SpriteInitializedComponent{false});
    initWaitingRoom();
    initGame();
    initSystem();
}

void Client::initSystem()
{
    _registry.register_system<Scene>(new Scene(_registry), std::type_index(typeid(Scene)));
    _registry.systems.push_back(_registry._systems[std::type_index(typeid(Scene))]);
    _registry.register_system<ShootSystemClient>(new ShootSystemClient(_registry), std::type_index(typeid(ShootSystemClient)));
    _registry.systems.push_back(_registry._systems[std::type_index(typeid(ShootSystemClient))]);
    _registry.register_system<TextBoxSystem>(new TextBoxSystem(_registry), std::type_index(typeid(TextBoxSystem)));
    _registry.systems.push_back(_registry._systems[std::type_index(typeid(TextBoxSystem))]);
    _registry.register_system<MobEnemyClient>(new MobEnemyClient(_registry), std::type_index(typeid(MobEnemyClient)));
    _registry.systems.push_back(_registry._systems[std::type_index(typeid(MobEnemyClient))]);
    _registry.register_system<GuiSystem>(new GuiSystem(_registry), std::type_index(typeid(GuiSystem)));
    _registry.systems.push_back(_registry._systems[std::type_index(typeid(GuiSystem))]);
    _registry.register_system<CollisionSystemClient>(new CollisionSystemClient(_registry), std::type_index(typeid(CollisionSystemClient)));
    _registry.systems.push_back(_registry._systems[std::type_index(typeid(CollisionSystemClient))]);
    _registry.register_system<SoundSystem>(new SoundSystem(_registry), std::type_index(typeid(SoundSystem)));
    _registry.systems.push_back(_registry._systems[std::type_index(typeid(SoundSystem))]);
    _registry.register_system<DestroyAnimSystem>(new DestroyAnimSystem(_registry), std::type_index(typeid(DestroyAnimSystem)));
    _registry.systems.push_back(_registry._systems[std::type_index(typeid(DestroyAnimSystem))]);
    _registry.register_system<ItemSystem>(new ItemSystem(_registry), std::type_index(typeid(ItemSystem)));
    _registry.systems.push_back(_registry._systems[std::type_index(typeid(ItemSystem))]);
    // _registry.register_system<GameOverSystem>(new GameOverSystem(_registry), std::type_index(typeid(GameOverSystem)));
    // _registry.systems.push_back(_registry._systems[std::type_index(typeid(GameOverSystem))]);
    // _registry.register_system<WeaponSystem>(new WeaponSystem(_registry), std::type_index(typeid(WeaponSystem)));
    // _registry.systems.push_back(_registry._systems[std::type_index(typeid(WeaponSystem))]);
    _registry.register_system<EnemyShootSystemClient>(new EnemyShootSystemClient(_registry), std::type_index(typeid(EnemyShootSystemClient)));
    _registry.systems.push_back(_registry._systems[std::type_index(typeid(EnemyShootSystemClient))]);
    _registry.register_system<Render>(new Render(_registry), std::type_index(typeid(Render)));
    _registry.systems.push_back(_registry._systems[std::type_index(typeid(Render))]);
}
