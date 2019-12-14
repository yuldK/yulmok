#include "player.h"

namespace omok
{
    player::player(state player_type)
        : my_state{ player_type }
        , my_board{}
    {
    }

    player::~player()
    {
    }

    void player::get(state player_type, coord coord)
    {
        my_board.put(player_type, coord);
    }

}
