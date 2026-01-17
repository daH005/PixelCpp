#pragma once

enum Direction {
    NO = 0,
    RIGHT = 1,
    LEFT = -1,
};

Direction flipDirection(Direction direction) {
    return (Direction)((int)direction * -1);
}
