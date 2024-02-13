/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** Server
*/

#include "../../include/Network/packets.hpp"
#include "../../include/Server/Server.hpp"

Server::Server(int port) : timer(io_context, asio::chrono::seconds(1))
{
    netwk = std::make_shared<network>(io_context, port);
    setComponent();
    setSystem();
    run = true;
    manageRequest();
    _exec = std::thread(&Server::run_service, this);
}

Server::~Server()
{
    run = false;
    io_context.stop();
    _exec.join();
}

void Server::manageRequest()
{
    netwk->async_receive(recv, std::bind(&Server::HandleReceive, this, std::placeholders::_1, std::placeholders::_2));
}

void Server::HandleReceive(asio::error_code const &error, std::size_t Bytes)
{
    int i  = (int)Message_header::getId(recv);
    std:: cout << "ID MESSAGE: " << i << std::endl;
    bool news = check_New_client(player_ntwk_address, netwk->getEnpointInfo());
    std::cout << "In System : " << news << std::endl;

    if (news == false && gamerun == false && nb_player < 4) {
        nb_player += 1;
        std::pair<udp::endpoint, int> nww_player(netwk->getEnpointInfo(), player_id);
        player_ntwk_address.push_back(nww_player);
        player_id += 1;
        recv_msg_client.push(std::pair<udp::endpoint, std::vector<u_int8_t>>(netwk->getEnpointInfo(), recv));
    } else if (news == true ) {
        std::lock_guard<std::mutex> lockk(RecvMutex);
        recv_msg_client.push(std::pair<udp::endpoint, std::vector<u_int8_t>>(netwk->getEnpointInfo(), recv));
    } else if (gamerun == true || nb_player == 4) {
        netwk->send(Message_header::HeaderSerialize(ROOM_FULL, std::string("0")), netwk->getEnpointInfo());
    }
    manageRequest();
}

void Server::CreatPlayerEntity(int player_id, udp::endpoint ip)
{
    auto new_player = _regist.spawn_entity();
    std::cout << new_player << std::endl;
    _regist.add_component<PositionComponent>(new_player, PositionComponent{50, 50, 166 / 5, 86 / 5});
    _regist.add_component<VelocityComponent>(new_player, VelocityComponent{50, 50});
    _regist.add_component<HealthComponent>(new_player, HealthComponent{100, true});
    _regist.add_component<PlayerID>(new_player, player_id);
    _regist.add_component<ScaleComponent>(new_player, ScaleComponent{4, 4});
    _regist.add_component<ShootableComponent>(new_player, ShootableComponent{true, ShootType::BASIC, int(new_player)});
    _regist.add_component<DrawableComponent>(new_player, DrawableComponent{true});
    _regist.add_component<SpriteInitializedComponent>(new_player, SpriteInitializedComponent{false});
    _regist.add_component<TextureComponent>(new_player, TextureComponent{SPACESHIP, false});
    _regist.add_component<AnimationComponent>(new_player, AnimationComponent{true, 0, 0.1f, 5, 5, 0, 0});
    _regist.add_component<InputComponent>(new_player, InputComponent{true});
    _regist.add_component<TeamComponent>(new_player, TeamComponent{TeamType::ALLY});
    _regist.add_component<DeadComponent>(new_player, DeadComponent{false, EntityType::PLAYER});
    _regist.add_component<ScoreComponent>(new_player, ScoreComponent{});
    _regist.add_component<DamageComponent>(new_player, DamageComponent{10, int(new_player), 0});
    _regist.add_component<DestroyedComponent>(new_player, DestroyedComponent{false, 0});
    _regist.add_component<SoundComponent>(new_player, SoundComponent{{"", SHOOT_SOUND, PLAYER_DEATH_SOUND}, 0});
    _regist.add_component<WeaponComponent>(new_player, WeaponComponent{false});

    if (!_regist.get_components<PositionComponent>()[new_player].has_value() ||
        !_regist.get_components<VelocityComponent>()[new_player].has_value()) {
        std::cerr << "Erreur : Un ou plusieurs composants sont manquants pour l'entité " << new_player << std::endl;
        exit(84);
    }

    all_clients[ip] = new_player;
    player_status[ip] = false;
}

void Server::setComponent()
{
    _regist.register_component<PlayerID>();
    auto init = _regist.spawn_entity();
    _regist.add_component<PositionComponent>(0, PositionComponent{0, 0, 0, 0});
    _regist.add_component<VelocityComponent>(0, VelocityComponent{0, 0});
    _regist.add_component<DrawableComponent>(0, DrawableComponent{false});
    _regist.add_component<TextureComponent>(0, TextureComponent{"", false});
    _regist.add_component<TextComponent>(0, TextComponent{"", "", 0});
    _regist.add_component<ScaleComponent>(0, ScaleComponent{0, 0});
    _regist.add_component<AnimationComponent>(0, AnimationComponent{false, 0, 0, 0, 0, 0, 0});
    _regist.add_component<InputComponent>(0, InputComponent{false});
    _regist.add_component<ShootableComponent>(0, ShootableComponent{false, ShootType::NO_SHOOT, 0});
    _regist.add_component<TeamComponent>(0, TeamComponent{TeamType::NO_TEAM});
    _regist.add_component<DeadComponent>(0, DeadComponent{false, EntityType::VOID});
    _regist.add_component<SpriteInitializedComponent>(0, SpriteInitializedComponent{false});
    _regist.add_component<DamageComponent>(0, DamageComponent{0, 0, 0});
    _regist.add_component<TextBoxComponent>(0, TextBoxComponent{0});
    _regist.add_component<HealthComponent>(0, HealthComponent{0, false});
    _regist.add_component<AIComponent>(0, AIComponent{false});
    _regist.add_component<CollisionComponent>(0, CollisionComponent{false});
    _regist.add_component<SoundComponent>(0, SoundComponent{{}, 0});
    _regist.add_component<WeaponComponent>(0, WeaponComponent{false});
    _regist.add_component<ScoreComponent>(0, ScoreComponent{});
    _regist.add_component<DropableComponent>(0, DropableComponent{false, 0, 0});
    _regist.add_component<GuiComponent>(0, GuiComponent{""});
    _regist.add_component<DestroyedComponent>(0, DestroyedComponent{false, 0});

    for (int i = 0; i < 49; i++) {
        auto any = _regist.spawn_entity();
    }
}

void Server::setSystem()
{
    _regist.register_system<MouvementSystem>(new MouvementSystem(_regist), std::type_index(typeid(MouvementSystem)));
    _regist.systems.push_back(_regist._systems[std::type_index(typeid(MouvementSystem))]);
    _regist.register_system<ShootSystem>(new ShootSystem(_regist), std::type_index(typeid(ShootSystem)));
    _regist.systems.push_back(_regist._systems[std::type_index(typeid(ShootSystem))]);
    _regist.register_system<CollisionSystem>(new CollisionSystem(_regist), std::type_index(typeid(CollisionSystem)));
    _regist.systems.push_back(_regist._systems[std::type_index(typeid(CollisionSystem))]);
    // _regist.register_system<ItemSystem>(new ItemSystem(_regist), std::type_index(typeid(ItemSystem)));
    // _regist.systems.push_back(_regist._systems[std::type_index(typeid(ItemSystem))]);
    // _regist.register_system<GameOverSystem>(new GameOverSystem(_regist), std::type_index(typeid(GameOverSystem)));
    // _regist.systems.push_back(_regist._systems[std::type_index(typeid(GameOverSystem))]);
    // _regist.register_system<WeaponSystem>(new WeaponSystem(_regist), std::type_index(typeid(WeaponSystem)));
    // _regist.systems.push_back(_regist._systems[std::type_index(typeid(WeaponSystem))]);
    _regist.register_system<EnemyShootSystem>(new EnemyShootSystem(_regist), std::type_index(typeid(EnemyShootSystem)));
    _regist.systems.push_back(_regist._systems[std::type_index(typeid(EnemyShootSystem))]);
    _regist.register_system<MobEnemy>(new MobEnemy(_regist), std::type_index(typeid(MobEnemy)));
    _regist.systems.push_back(_regist._systems[std::type_index(typeid(MobEnemy))]);
    _regist.register_system<MobEnemyServer>(new MobEnemyServer(_regist), std::type_index(typeid(MobEnemyServer)));
    _regist.systems.push_back(_regist._systems[std::type_index(typeid(MobEnemyServer))]);
}

bool Server::check_New_client(std::vector<std::pair<udp::endpoint, int>> address, udp::endpoint ip)
{
    bool know = false;

    for (size_t i = 0; i < address.size(); i++) {
        if (address[i].first.address() == ip.address() &&  address[i].first.port() == ip.port())
            know = true;
    }
    return know;
}

int Server::GetClientID(udp::endpoint ip)
{
    int id = -1;
    for (size_t i = 0; i < player_ntwk_address.size(); i++) {
        if (player_ntwk_address[i].first.address() == ip.address() &&  player_ntwk_address[i].first.port() == ip.port())
            id = player_ntwk_address[i].second;
    }
    return id;
}

udp::endpoint Server::GetClientEndpoint(int id_client)
{
    udp::endpoint ip;
    for (size_t i = 0; i < player_ntwk_address.size(); i++) {
        if (player_ntwk_address[i].second == id_client)
            ip = player_ntwk_address[i].first;
    }
    return ip;
}

void Server::SendData()
{
    if (send__msg_client.size() == 0) {
        return;
    }
    std::lock_guard<std::mutex> lock(SendMutex);
    while (send__msg_client.size() != 0) {
        auto msg = send__msg_client.front();
        udp::endpoint client_ip = msg.first;
        netwk->send(msg.second, client_ip);
        send__msg_client.pop();
    }
}

void Server::HandleRequest()
{
    if (recv_msg_client.size() == 0)
        return;
    int id;
    msg_string a;
    player_move n;
    inform_player_move move;
    inform_player_shoot shoot;
    kill_player kill;
    auto msg = recv_msg_client.front();
    id = (int)Message_header::getId(msg.second);

    switch (id) {
        case (0):
            a = serializable_system<msg_string>::deserialize(Message_header::extractMessageWithoutId(msg.second));
            std::cout << "name: " << a.data << std::endl;
            player_name[msg.first] = a.data;
            CreatPlayerEntity(GetClientID(msg.first), msg.first);
            SendRoominfoPlayer();
            break;
        case (1):
            std::cout << "deconnect player with id " << GetClientID(msg.first) << std::endl;
            MessageAllclient(Message_header::HeaderSerialize(DISCONNECTION, inform_player_disconnected(GetClientID(msg.first))));
            deconnect_player(msg.first);
            break;
         case (2):
            n = serializable_system<player_move>::deserialize(Message_header::extractMessageWithoutId(msg.second));
            MovePlayer(all_clients[msg.first], n.diretion_player);
            break;
         case (3): {
                std::cout << "player with id " << GetClientID(msg.first) << " shoot" << std::endl;
                //shoot = inform_player_shoot(getEntityIdPlayer(msg.first));
                _regist.indexedParams["playerController"] = int(all_clients[msg.first]);
                //MessageAllclient(Rooms->GetEntityPlayersID(), Message_header::HeaderSerialize(SHOOT_PLAYER, shoot), getEntityIdPlayer(msg.first));
            break;
        }
        case (4):
            std::cout << "player with id " << msg.first << " Ready" << std::endl;
            player_status[msg.first] = player_status[msg.first] == false ? true : false;
            nb_player_ready += 1;
            SendRoominfoPlayer();
            break;
        case (5):
            kill = serializable_system<kill_player>::deserialize(Message_header::extractMessageWithoutId(msg.second));
            // if (getEntityIdPlayer(msg.first) == Rooms->GetAdminId()) {
            //     MessageAllclient(Rooms->GetEntityPlayersID(), Message_header::HeaderSerialize(DISCONNECTION, inform_player_disconnected(kill.id_enitity)));
            //     Rooms->leave_room(kill.id_enitity);
            //     deconnect_player(getIDplayerEntity(kill.id_enitity));
            // }
            break;
        case 19:
            Rooms->ReduxMaxplayer(3);
            //Rooms->add_player_ready(getEntityIdPlayer(msg.first));
            Rooms->CheckRunning();
            break;
    }
    if (gamerun != true) {
        gamerun = nb_player_ready == nb_player ? true : false;
        if (gamerun == true) {
            InfoGameReady();
            std::cout << "test here" << std::endl;
            if (!ecs_thread.joinable())
                ecs_thread = std::thread(&Server::RunECSServer, this);
        }
    }
    std::lock_guard<std::mutex> lockk(RecvMutex);
    recv_msg_client.pop();
}

void Server::create_ennemy() {
    if (std::any_cast<mobClass>(_regist.indexedParams["mob"])._id > 0 &&
    std::any_cast<mobClass>(_regist.indexedParams["mob"])._x > 0 &&
    std::any_cast<mobClass>(_regist.indexedParams["mob"])._y > 0) {
        int mob = std::any_cast<mobClass>(_regist.indexedParams["mob"])._id;
        int x = std::any_cast<mobClass>(_regist.indexedParams["mob"])._x;
        int y = std::any_cast<mobClass>(_regist.indexedParams["mob"])._y;
        int type = std::any_cast<mobClass>(_regist.indexedParams["mob"])._type;
        new_ennemy enemy(x, y, type, mob);
        MessageAllclient(Message_header::HeaderSerialize(NEW_ENEMY, enemy));
        //std::cout << "ID: " << mob << std::endl;
    }
}

void Server::create_bullet() {
    if (std::any_cast<mobClass>(_regist.indexedParams["bullet"])._id > 0 &&
    std::any_cast<mobClass>(_regist.indexedParams["bullet"])._x > 0 &&
    std::any_cast<mobClass>(_regist.indexedParams["bullet"])._y > 0) {
        std::any storedValue = _regist.indexedParams["bullet"];
        mobClass& _bulletSend = std::any_cast<mobClass&>(storedValue);
        int mob = std::any_cast<mobClass>(_regist.indexedParams["bullet"])._id;
        double x = std::any_cast<mobClass>(_regist.indexedParams["bullet"])._x;
        double y = std::any_cast<mobClass>(_regist.indexedParams["bullet"])._y;
        int type = std::any_cast<mobClass>(_regist.indexedParams["bullet"])._type;
        int idPlayer = std::any_cast<int>(_regist.indexedParams["playerController"]);

        //std::cout << "ID: " << mob << std::endl;

        new_allyBullet bullet(x, y, type, mob, idPlayer);
        MessageAllclient(Message_header::HeaderSerialize(SHOOT_PLAYER, bullet));
        _regist.indexedParams["playerController"] = int(0);
        _bulletSend._id = 0;
        _bulletSend._x = 0;
        _bulletSend._y = 0;
        _bulletSend._type = 0;
        _regist.indexedParams["bullet"] = _bulletSend;
    }
}

void Server::create_item() {
    if (std::any_cast<itemStruct>(_regist.indexedParams["item"])._id > 0 &&
    std::any_cast<itemStruct>(_regist.indexedParams["item"])._x > 0 &&
    std::any_cast<itemStruct>(_regist.indexedParams["item"])._y > 0) {
        std::any storedValue = _regist.indexedParams["item"];
        itemStruct& _itemSend = std::any_cast<itemStruct&>(storedValue);
        int item = std::any_cast<itemStruct>(_regist.indexedParams["item"])._id;
        double x = std::any_cast<itemStruct>(_regist.indexedParams["item"])._x;
        double y = std::any_cast<itemStruct>(_regist.indexedParams["item"])._y;

        new_item items(x, y, item);
        MessageAllclient(Message_header::HeaderSerialize(NEW_ITEM, items));
        _itemSend._id = 0;
        _itemSend._x = 0;
        _itemSend._y = 0;
        _regist.indexedParams["item"] = _itemSend;
    }
}

void Server::create_ennemy_bullet() {
    if (std::any_cast<enemyShootClass>(_regist.indexedParams["enemyShoot"])._idBullet.size() > 0) {
        std::any storedValue = _regist.indexedParams["enemyShoot"];
        enemyShootClass& _bulletSend = std::any_cast<enemyShootClass&>(storedValue);
        std::vector<int> bullet = std::any_cast<enemyShootClass>(_regist.indexedParams["enemyShoot"])._idBullet;
        std::vector<int> player = std::any_cast<enemyShootClass>(_regist.indexedParams["enemyShoot"])._idPlayer;
        for (size_t i = 0; i < bullet.size(); ++i) {
            new_ennemy_bullet bulletSend(bullet[i], player[i]);
            MessageAllclient(Message_header::HeaderSerialize(NEW_ENEMY_BULLET, bulletSend));
            std::cout << "Bullet ID: " << bullet[i] << std::endl;
        }
        _bulletSend._idBullet.clear();
        _bulletSend._idPlayer.clear();
        _regist.indexedParams["enemyShoot"] = _bulletSend;
    }
}

void Server::move_ennemy_entity() {
    if (std::any_cast<entityMoveClass>(_regist.indexedParams["entityMove"])._idEntity.size() > 0) {
        std::any storedValue = _regist.indexedParams["entityMove"];
        entityMoveClass& _entitySend = std::any_cast<entityMoveClass&>(storedValue);
        std::vector<int> entity = std::move(_entitySend._idEntity);
        std::vector<int> posX = std::move(_entitySend._idPosX);
        std::vector<int> posY = std::move(_entitySend._idPosY);

        for (size_t i = 0; i < entity.size(); ++i) {
            update_player_position entitySend(entity[i], posX[i], posY[i]);
            MessageAllclient(Message_header::HeaderSerialize(MOVE_PLAYER, entitySend));
        }

        _entitySend._idEntity.clear();
        _entitySend._idPosX.clear();
        _entitySend._idPosY.clear();
        _regist.indexedParams["entityMove"] = std::move(_entitySend);
    }
}

void Server::MovePlayer(Registry::entity_t &entity, uint16_t direction)
{
    std::cout << "player " << entity << " Direction: " << direction << std::endl;
    auto &positionComp = _regist.get_components<PositionComponent>();
    auto const &velocityComp = _regist.get_components<VelocityComponent>();
    auto &position = positionComp[entity];
    auto const &velocity = velocityComp[entity];
    switch (direction) {
        case Control::UP:
            position->_y = (position->_y - velocity->_y <= 50) ? 50 : position->_y - velocity->_y;
        break;
        case Control::DOWN:
            position->_y = (position->_y + velocity->_y >= 830) ? 830 : position->_y + velocity->_y;
        break;
        case Control::LEFT:
            position->_x = (position->_x - velocity->_x <= 50) ? 50 : position->_x - velocity->_x;
        break;
        case Control::RIGHT:
            position->_x = (position->_x + velocity->_x >= 1640) ? 1640 : position->_x + velocity->_x;
        break;
    }
    update_player_position pos_update(entity, position->_x, position->_y);
    MessageAllclient(Message_header::HeaderSerialize(MOVE_PLAYER, pos_update));
}

void Server::UpdatePlayer()
{
    auto &health = _regist.get_components<HealthComponent>();
    for (int i = 0; i < player_ntwk_address.size(); i++) {
        auto &player_health = health[all_clients[player_ntwk_address[i].first]];
        //std::cout << player_ntwk_address[i].second <<" CUR" << player_health->_current_health << " MAX " << player_health->_max_health << std::endl;
        if (player_health->_current_health < player_health->_max_health) {
            MessageAllclient(Message_header::HeaderSerialize(UPDATE_PLAYER_HEALTH, update_player_health(all_clients[player_ntwk_address[i].first], player_health->_current_health)));
            player_health->_max_health = player_health->_current_health;
            if (player_health->_current_health == 0) {
                send__msg_client.push(std::pair<udp::endpoint, std::vector<uint8_t>>(player_ntwk_address[i].first, Message_header::HeaderSerialize(END_GAME, update_player_health(all_clients[player_ntwk_address[i].first], player_health->_current_health))));
            }
        }
    }
}
// void Server::MessageAllclient(std::vector<uint8_t> msg)
// {
//     int id;
//     for (size_t i = 0; i < player_ntwk_address.size(); i++) {
//         id = player_ntwk_address[i].second;
//         send__msg_client.push(std::pair<int, std::vector<uint8_t>>(id, msg));
//     }
// }

void Server:: MessageAllclient(std::vector<uint8_t> msg)
{
    std::lock_guard<std::mutex> lock(SendMutex);
    for (size_t i = 0; i < player_ntwk_address.size(); i++) {
        send__msg_client.push(std::pair<udp::endpoint, std::vector<uint8_t>>(player_ntwk_address[i].first, msg));
    }
}

// void Server::MessageAllclient(std::vector<uint8_t> msg, std::vector<std::pair<udp::endpoint, int>> player_address, udp::endpoint client_except)
// {
//     int id;
//     for (size_t i = 0; i < player_address.size(); i++) {
//         if (player_address[i].first != client_except) {
//             id = player_address[i].second;
//             send__msg_client.push(std::pair<int, std::vector<uint8_t>>(id, msg));
//         }
//     }
// }

// void Server:: MessageAllclient(std::vector<int> address, std::vector<uint8_t> msg)
// {
//     int id = -1;
//     for (size_t i = 0; i < address.size(); i++) {
//         id = getIDplayerEntity(address[i]);
//         if (id != -1)
//             send__msg_client.push(std::pair<int, std::vector<uint8_t>>(id, msg));
//     }
// }

// void Server::MessageAllclient(std::vector<int> address, std::vector<uint8_t> msg, int client_except)
// {
//     int id = -1;
//     for (size_t i = 0; i < address.size(); i++) {
//         if (address[i] != client_except) {
//             id = getIDplayerEntity(address[i]);
//             if (id != -1)
//                 send__msg_client.push(std::pair<int, std::vector<uint8_t>>(id, msg));
//         }
//     }
// }

void Server::deconnect_player(udp::endpoint ip)
{
    int i = -1;

    for (size_t v = 0; v < player_ntwk_address.size(); v++) {
        if (player_ntwk_address[v].first == ip) {
            i = v;
            break;
        }
    }
    if (i == -1)
        return;
    player_ntwk_address.erase(player_ntwk_address.begin() + i);
    player_status.erase(ip);
    player_name.erase(ip);
    all_clients.erase(ip);
}

/*void Server::GameRoomLoop(std::shared_ptr<Room> room)
{
    int id;
    player_move n;
    inform_player_move move;
    inform_player_shoot shoot;
    while (room->GetSateRoom() == true) {
        auto msg = room->getMessageFront();
        id = (int)Message_header::getId(msg.second);
        switch (id) {
        case 2:
            n = serializable_system<player_move>::deserialize(Message_header::extractMessageWithoutId(msg.second));
            move = inform_player_move(msg.first, n.diretion_player);
            MessageAllclient(room->GetEntityPlayersID(), Message_header::HeaderSerialize(MOVE_PLAYER, n), msg.first);
            break;
        case 3:
            shoot = inform_player_shoot(msg.first);
            MessageAllclient(room->GetEntityPlayersID(), Message_header::HeaderSerialize(SHOOT_PLAYER, shoot), msg.first);
            break;
        }
    }
}*/

void Server::SendRoominfoPlayer()
{
    int w = 0;
    players_states states;
    std::vector<std::pair<std::string, bool>> info;
    for (int i = 0; i < player_ntwk_address.size(); i++) {
        info.push_back(std::make_pair(player_name[player_ntwk_address[i].first], player_status[player_ntwk_address[i].first]));
    }
    for (size_t i = 0; i < info.size(); i++) {
        memcpy(&states.names[w], info[i].first.c_str(), sizeof(info[i].first.c_str()));
        states.states_player[w] = info[i].second;
        w++;
    }
    std::lock_guard<std::mutex> lock(SendMutex);
    for (size_t i = 0; i < player_ntwk_address.size(); i++) {
        udp::endpoint ip = player_ntwk_address[i].first;
        send__msg_client.push(std::pair<udp::endpoint, std::vector<uint8_t>>(ip, Message_header::HeaderSerialize(NEW_CLIENT, states)));
    }
}

void Server::SendPlayerStartGame(std::pair<asio::ip::udp::endpoint, int> id, std::vector<std::pair<asio::ip::udp::endpoint, int>> player_ntwk_address)
{
    info_all_player new_msg(id.second);
    int x = 0;

    for (size_t i = 0; i < player_ntwk_address.size(); i++) {
        if (player_ntwk_address[i].second != id.second) {
            new_msg.id_enitity_players[x] = player_ntwk_address[i].second;
            x++;
        }
    }
    std::lock_guard<std::mutex> lock(SendMutex);
    send__msg_client.push(std::pair<asio::ip::udp::endpoint, std::vector<uint8_t>>(id.first, Message_header::HeaderSerialize(START_GAME, new_msg)));
}

void Server::InfoGameReady()
{
    for (size_t i = 0; i < player_ntwk_address.size(); i++)
        SendPlayerStartGame(player_ntwk_address[i], player_ntwk_address);
}

void Server::RunECSServer() {
    asio::chrono::seconds starter(5);
    timer.expires_at(timer.expires_at() + starter);

    io_context.post([this, starter]() {
        std::this_thread::sleep_for(starter);
        asio::chrono::milliseconds timerInterval(15);

        while (gamerun == true) {
            std::this_thread::sleep_for(timerInterval);
            for (System* system : _regist.systems)
                system->callSystem();
            create_ennemy();
            create_ennemy_bullet();
            move_ennemy_entity();
            create_bullet();
            create_item();
            UpdatePlayer();
        }
    });
    io_context.run();
}

void Server::Execute()
{
    std::cout << "Server running...." << std::endl;
    while (run) {
        HandleRequest();
        SendData();
    }
}