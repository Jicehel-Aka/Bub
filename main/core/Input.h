/**
 * @file Input.h
 * @brief Etat des entrees (touches maintenues + fronts montants).
 */

#pragma once

struct InputState
{
    // Maintenues
    bool up = false, down = false, left = false, right = false;
    bool a = false, b = false, menu = false, run = false;

    // Fronts montants (appui a cette frame)
    bool upP = false, downP = false, leftP = false, rightP = false;
    bool aP = false, bP = false;
};

class Input
{
public:
    //! Lit le materiel (via la coquille) et met a jour l'etat.
    void update();

    const InputState& getState() const { return state; }

private:
    InputState state{};
};
