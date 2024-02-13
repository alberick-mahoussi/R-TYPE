/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** SoundSystem
*/

#ifndef SOUNDSYSTEM_HPP_
#define SOUNDSYSTEM_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class SoundSystem : public System {
    public:
        SoundSystem(Registry &registry) : _registry(registry) {
            for (int i = 0; i < MAX_SOUND_INSTANCES; i++) {
                sf::Sound sound;
                soundInstances.push_back(sound);
            }
        };
        ~SoundSystem();
        void callSystem() {
            auto &SoundComp = _registry.get_components<SoundComponent>();
            auto &DeadComp = _registry.get_components<TeamComponent>();
            
            for (size_t i = 0; i < SoundComp.size(); ++i) {
                auto &sound = SoundComp[i];
                auto &team = DeadComp[i];
                if (sound && (sound->_path.size() > 0 && sound->_index > 0 && (sound->_index <= sound->_path.size()))) {
                    if (loadedSound.find(sound->_path[sound->_index]) == loadedSound.end()) {
                        sf::SoundBuffer soundBufferTmp;
                        if (soundBufferTmp.loadFromFile(sound->_path[sound->_index])) {
                            loadedSound[sound->_path[sound->_index]] = soundBufferTmp;
                        }
                    } 
                    if (loadedSound.find(sound->_path[sound->_index]) != loadedSound.end()) {
                        sf::SoundBuffer &buffer = loadedSound[sound->_path[sound->_index]];
                        sf::Sound* availableSoundInstance = getAvailableSoundInstance();
                        if (availableSoundInstance) {
                            availableSoundInstance->setBuffer(buffer);
                            availableSoundInstance->play();
                            sound->_index = 0;
                        }
                    }
                }
            }
        }

    protected:
    private:
        Registry &_registry;
        std::unordered_map<std::string, sf::SoundBuffer> loadedSound;
        std::vector<sf::Sound> soundInstances;
        static const int MAX_SOUND_INSTANCES = 10; // Vous pouvez ajuster le nombre d'instances selon vos besoins
        sf::Sound* getAvailableSoundInstance() {
            for (sf::Sound& soundInstance : soundInstances) {
                if (soundInstance.getStatus() != sf::Sound::Playing) {
                    return &soundInstance;
                }
            }
            return nullptr; // Aucune instance disponible
        }
};

#endif /* !SOUNDSYSTEM_HPP_ */
