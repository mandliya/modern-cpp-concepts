#include <iostream>

/* old way */
namespace engine {
    namespace game {
        namespace player {
            namespace character {
                int character_type;
            }
        }
    }
}

/* new way */
namespace engine::game::player::action {
    int move;
}

int main() {
    engine::game::player::character::character_type = 4;
    engine::game::player::action::move = 1;
    std::cout << "Player character type is :"
        << engine::game::player::character::character_type << std::endl
        << "Player action is :"
        << engine::game::player::action::move << std::endl;
    return 0;
}