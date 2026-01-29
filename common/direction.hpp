#pragma once

enum Direction {
    NO = 0,
    RIGHT = 1,
    LEFT = -1,
};

Direction flipDirection(Direction direction) {
    return (Direction)((int)direction * -1);
}

Direction defineDirection(int number) {
    if (number < 0) {
        return Direction::LEFT;

    } else {
        return Direction::RIGHT;

    }
}
