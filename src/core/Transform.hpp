#pragma once
#include <glm/glm.hpp>

// Class responsavel por conter as matrizes de rotacao, escala e translação que serão aplicadas nos objetos na cena, a class Transform
// será instanciada dentro de SceneObject3D dessa forma obteremos a model do objeto ao usar a função membro "glm::mat4 getModelMatrix() const"

//@@TODO: Adicionar uma verificação de mudança na model para não computar a multiplicação RTS e usar a model que está na memoria
class Transform
{
    public:
        Transform() = default;
        Transform(const glm::vec3 &scale,const glm::vec3 &translation ,const glm::vec3 &rotation, float rotationAngleDegrees);

        void setPosition(const glm::vec3 &position);
        void setRotation(const glm::vec3 &eulerAngles);
        void setScale(const glm::vec3 &scale);
        void setRotationAngleDeegres(float angle);

        glm::mat4 getModelMatrix() const;
    public:

    private:
        glm::vec3 _scale =  glm::vec3(1.0f);
		glm::vec3 _translation = glm::vec3(0.0f);
        glm::vec3 _rotation = glm::vec3(1.0f);

        float _rotationAngleDegrees; // Angle in degrees

};