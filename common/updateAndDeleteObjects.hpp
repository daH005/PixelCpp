#pragma once

template <typename T>
void updateAndDeleteObjects(T& objects) {
    for (auto it = objects.begin(); it != objects.end(); ) {
        it->update();
        if (it->getToBeDeleted()) {
            it = objects.erase(it);
        }
        else {
            ++it;
        }
    }
}
