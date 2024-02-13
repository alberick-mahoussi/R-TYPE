/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** Render
*/

#ifndef RENDER_HPP_
#define RENDER_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class Render : public System {
    public:
        Render(Registry &registry) : _registry(registry) {
            _window.create(sf::VideoMode(1920, 1080), "R-TYPE Epitech 2024");
            _window.setFramerateLimit(60);
            _window.setVerticalSyncEnabled(true);
            startTime = std::chrono::high_resolution_clock::now();
            currentTime = std::chrono::high_resolution_clock::now();
            if (!_font.loadFromFile(FONT_FAMILY)) {
                std::cerr << "Error : Cannot load font." << std::endl;
            }
        };
        ~Render();
        sf::Color stringToSFMLColor(const std::string& colorStr) {
            if (colorStr == "white") {
                return sf::Color::White;
            } else if (colorStr == "black") {
                return sf::Color::Black;
            } else if (colorStr == "red") {
                return sf::Color::Red;
            }
            return sf::Color::Transparent;
        };
        std::vector<sf::IntRect> createAnimationFrames(int frameWidth, int frameHeight, int rows, int cols, int posX, int posY) {
            std::vector<sf::IntRect> frames;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    int x = j * frameWidth;
                    int y = i * frameHeight;
                    frames.push_back(sf::IntRect(x + posX, y + posY, frameWidth, frameHeight));
                }
            }
            return frames;
        };
        void manageNav(std::string scene) {
            _state = 1;
            if (scene == "Play")
                _registry.setScene("LoginScreen");
            else if (scene == "WaitingScreen") {
                _registry.indexedParams["command"] = std::string("disconnect");
                _registry.setScene("LoginScreen");
            }
            else if (scene == "LoginScreen")
                _registry.setScene("Menu");
        }
        void selectedBtn(int _state) {
            int size = 0;
            double pos = 0.0f;
            _registry.add_component<TextComponent>(3, TextComponent{"PLAY", "white", size = (_state == 1) ? 60 * 1.45 : 60});
            _registry.add_component<PositionComponent>(3, PositionComponent{175.0f, pos = (_state == 1) ? 500.0f - ((size * 1.45) / 4) : 500.0f, 0, 0});
            _registry.add_component<TextComponent>(4, TextComponent{"SETTINGS", "white", size = (_state == 2) ? 60 * 1.45 : 60});
            _registry.add_component<PositionComponent>(4, PositionComponent{175.0f, pos = (_state == 2) ? 625.0f - ((size * 1.45) / 4) : 625.0f, 0, 0});
            _registry.add_component<TextComponent>(5, TextComponent{"EXIT", "white", size = (_state == 3) ? 60 * 1.45 : 60});
            _registry.add_component<PositionComponent>(5, PositionComponent{175.0f, pos = (_state == 3) ? 750.0f - ((size * 1.45) / 4) : 750.0f, 0, 0});

            _registry.add_component<TextComponent>(7, TextComponent{"Username: ", "white", size = (_state == 1) ? 40 * 1.45 : 40});
            _registry.add_component<PositionComponent>(7, PositionComponent{600.f, pos = (_state == 1) ? 300.0f - ((size * 1.45) / 4) : 300.0f, 0, 0});
            _registry.add_component<TextComponent>(9, TextComponent{"IP adress: ", "white", size = (_state == 2) ? 40 * 1.45 : 40});
            _registry.add_component<PositionComponent>(9, PositionComponent{600.f, pos = (_state == 2) ? 450.0f - ((size * 1.45) / 4) : 455.0f, 0, 0});
            _registry.add_component<TextComponent>(11, TextComponent{"Port: ", "white", size = (_state == 3) ? 40 * 1.45 : 40});
            _registry.add_component<PositionComponent>(11, PositionComponent{600.f, pos = (_state == 3) ? 600.0f - ((size * 1.45) / 4) : 600.0f, 0, 0});
        }
        void eventKeyMenu(sf::Event event)
        {
            _elapsed = _clock.getElapsedTime();
            // std::any &firstArg = _scene;
            // std::string _registry.setScene(std::any_cast<std::string>(firstArg);
            std::unordered_map<int, std::string> &storedMap = std::any_cast<std::unordered_map<int, std::string>&>(_registry.indexedParams["textBox"]);
            sf::Keyboard::Key key = event.key.code;
            if (_registry.getScene() == "LoginScreen") {
                if (key == sf::Keyboard::BackSpace && !storedMap[_state].empty())
                    storedMap[_state].pop_back();
                if (storedMap[_state].size() < 16) {
                    if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
                        storedMap[_state] += static_cast<char>(key + 97);
                    else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)
                        storedMap[_state] += static_cast<char>(key + 22);
                    else if (key == 51)
                        storedMap[_state] += static_cast<char>('4');
                    else if (key == 56)
                        storedMap[_state] += static_cast<char>('6');
                    else if (key == sf::Keyboard::Space)
                        storedMap[_state] += static_cast<char>('.');
                }
                storedMap[_state] = storedMap[_state];
            }
            if (key == sf::Keyboard::Up) {
                _registry.indexedParams["input"] = int(Control::UP);
                _state = (_state <= 1) ? MenuType::EXIT : _state - 1;
            }
            if (key == sf::Keyboard::Down) {
                _registry.indexedParams["input"] = int(Control::DOWN);
                _state = (_state >= MenuType::EXIT) ? MenuType::PLAY : _state + 1;
            }
            if (key == sf::Keyboard::Left) {
                _registry.indexedParams["input"] = int(Control::LEFT);
            }
            if (key == sf::Keyboard::Right) {
                _registry.indexedParams["input"] = int(Control::RIGHT);
            }
            if (key == sf::Keyboard::Escape) {
                manageNav(_registry.getScene());
            }
            if (key == sf::Keyboard::R) {
                if (_registry.getScene() == "WaitingScreen") {
                    _registry.indexedParams["command"] = std::string("ready");
                }
            }
            if (key == sf::Keyboard::Space) {
                if ((_elapsed.asSeconds() >= 0.5f)) {
                    _registry.indexedParams["input"] = int(Control::SPACE);
                    _clock.restart();
                }
            }
            if (_registry.getScene() == "LoginScreen") {
                if (key == sf::Keyboard::Enter) {
                    _registry.indexedParams["command"] = std::string("connection");
                }
            }
            if (_registry.getScene() == "Menu") {
                if (key == sf::Keyboard::Enter) {
                    switch (_state) {
                    case MenuType::PLAY:
                        _state = 1;
                        _registry.setScene("LoginScreen");
                        break;
                    case MenuType::SETTINGS:
                        _registry.setScene("Play");
                        break;
                    case MenuType::EXIT:
                        _window.close();
                        _registry.indexedParams["command"] = std::string("close");
                        break;
                    }
                }
            }
        }
        void windowEvent() {
            selectedBtn(_state);
            sf::Event event;
            while (_window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed: {
                        _window.close();
                        _registry.indexedParams["command"] = std::string("close");
                        break;
                    case sf::Event::KeyPressed:
                        eventKeyMenu(event);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        void callSystem() {
            auto &positionsComp = _registry.get_components<PositionComponent>();
            auto &initializedComp = _registry.get_components<SpriteInitializedComponent>();
            auto &textureComp = _registry.get_components<TextureComponent>();
            auto &textComp = _registry.get_components<TextComponent>();
            auto &drawableComp = _registry.get_components<DrawableComponent>();
            auto &scaleComp = _registry.get_components<ScaleComponent>();
            auto &animationComp = _registry.get_components<AnimationComponent>();
            currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = currentTime - startTime;
            startTime = currentTime;

            windowEvent();

            _window.clear(sf::Color::Black);
            for (size_t entity = 1; entity <= drawableComp.size() - 1; entity++) {
                auto &text = textComp[entity];
                auto &drawable = drawableComp[entity];
                auto &initialized = initializedComp[entity];
                auto &texture = textureComp[entity];
                auto &position = positionsComp[entity];
                auto &scale = scaleComp[entity];
                auto &animation = animationComp[entity];

                if (drawable && initialized && (drawable->_draw == true && initialized->_initializedComponent == true)) {
                    if (texture) {
                        if (loadedTextures.find(texture->_path) != loadedTextures.end()) {
                            sf::Sprite sprite;
                            sprite.setTexture(loadedTextures[texture->_path]);
                            if (animation && (animation->_animed == true)) {
                                    _animationFrames = createAnimationFrames(position->_wth, position->_hgt, animation->_row, animation->_column, animation->_posX, animation->_posY);
                                    sprite.setTextureRect(_animationFrames[animation->_currentFrame]);
                                    _deltaTime = elapsed.count();
                                    animation->_frameTime -= _deltaTime;
                                    if (animation->_frameTime <= 0) {
                                        static int direction = 1;
                                        animation->_currentFrame += direction;
                                        if (animation->_currentFrame >= animation->_column || animation->_currentFrame < 0) {
                                            direction *= -1;
                                            animation->_currentFrame += direction;
                                        }
                                        animation->_frameTime = 0.15f;
                                    }
                            }
                            // sf::RectangleShape square(sf::Vector2f(position->_wth * scale->_scaleX - 5, position->_hgt * scale->_scaleY - 5));
                            // square.setPosition(position->_x + 5, position->_y + 5);
                            // square.setFillColor(sf::Color::White);
                            sprite.setPosition(position->_x, position->_y);
                            sprite.setColor(sf::Color::White);
                            if (scale)
                                sprite.setScale(scale->_scaleX, scale->_scaleY);

                            if (texture->_shader == true) {
                                _backgroundGame.setUniform("offset", _offset += _clockShader.restart().asSeconds() / 10);
                                _window.draw(sprite, &_backgroundGame);
                            } else {
                                // _window.draw(square);
                                _window.draw(sprite);
                            }
                        }
                    } else if (text) {
                        sf::Text &drawText = _text[entity];
                        drawText.setString(text->_word);
                        drawText.setCharacterSize(text->_size);
                        drawText.setPosition(position->_x, position->_y);
                        _window.draw(drawText);
                    }
                }
                if (drawable && initialized && (drawable->_draw == true && initialized->_initializedComponent == false)) {
                    if (text) {
                        sf::Text initText;

                        initText.setFont(_font);
                        initText.setCharacterSize(text->_size);
                        initText.setString(text->_word);
                        initText.setPosition(position->_x, position->_y);
                        initText.setFillColor(stringToSFMLColor(text->_color));
                        _text[entity] = initText;
                        initialized->_initializedComponent = true;
                    } else if (texture) {
                        if (loadedTextures.find(texture->_path) == loadedTextures.end()) {
                            sf::Texture textureTmp;
                            if (textureTmp.loadFromFile(texture->_path)) {
                                if (texture->_shader == true) {
                                    textureTmp.setRepeated(true);
                                    if (!_backgroundGame.loadFromFile(SHADER, sf::Shader::Vertex)) {
                                        std::cout << "Error: Could not load shader from file!" << std::endl;
                                    }
                                }
                                loadedTextures[texture->_path] = textureTmp;
                            }
                        }
                        initialized->_initializedComponent = true;
                    }
                }
            }
            _window.display();
        }

    private:
        Registry &_registry;
        std::unordered_map<std::string, sf::Texture> loadedTextures;
        std::unordered_map<int, sf::Text> _text;
        sf::Shader _backgroundGame;
        float _offset = 0.f;
        sf::Clock _clockShader;
        sf::Clock _clockAnim;
        std::vector<sf::IntRect> _animationFrames;
        float _deltaTime;
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point currentTime;
        sf::Clock _clock;
        sf::Time _elapsed;
        sf::RenderWindow _window;
        int _state = 1;
        sf::Font _font;
};

#endif /* !RENDER_HPP_ */
