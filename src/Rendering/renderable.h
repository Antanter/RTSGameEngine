//
// Created by Andrii Klykavka on 14.07.2025.
//

#ifndef RENDERABLE_H
#define RENDERABLE_H

class Renderable {
public:
    virtual void render(float, float, float, float) = 0;
    virtual ~Renderable() = default;
};

#endif //RENDERABLE_H
