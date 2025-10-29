#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr
#include <iostream>

Transform::Transform(const glm::vec3 &scale, const glm::vec3 &translation, const glm::vec3 &rotation, float rotationAngleDegrees)
:   _scale{scale}, _translation{translation}, _rotation{rotation}, _rotationAngleDegrees{rotationAngleDegrees}
{
}

void Transform::setPosition(const glm::vec3 &position)
{
    _translation = position;
}

void Transform::setRotation(const glm::vec3 &eulerAngles)
{
    _rotation = eulerAngles;
}

void Transform::setScale(const glm::vec3 &scale)
{
    _scale = scale;
}

void Transform::setRotationAngleDeegres(float angle)
{
    _rotationAngleDegrees = angle;
}

glm::mat4 Transform::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::scale(model, _scale);
    
    model = glm::rotate(model, glm::radians(_rotationAngleDegrees),_rotation);
    
    model = glm::translate(model, _translation);

    return model;
}

float Transform::getRotationAngle()
{
    return _rotationAngleDegrees;
}
