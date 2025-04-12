#include "../include/Move.h"
#include "../include/General.h"

Move::Move() {
    progress = 0;
    pointer = 0;
}
int Move::getVertexDone() const {
    if (progress == pointer) return pointer;
    else return -1;
}
int Move::size() const {
    return m_vertices.size();
}
float Move::getProgress() const {
    return progress;
}
void Move::handle() {
    if (progress != pointer) {
        Vector2 delta = m_vertices[pointer] - getPosition();
        if (abs(pointer-progress)>0.001) {
            Vector2 pos = getPosition() + delta/10;
            progress += (pointer-progress)/10;
            setPosition(pos.x, pos.y);
        } else {
            setPosition(m_vertices[pointer].x, m_vertices[pointer].y);
            progress = pointer;
        }
    }
}
void Move::skip() {
    setPosition(m_vertices[pointer].x, m_vertices[pointer].y);
    progress = pointer;
}
void Move::setVerticesPosition(const float& x, const float& y) {
    for (int i = 0; i<m_vertices.size(); i++) {
        m_vertices[i] = m_vertices[i] - getPosition() + Vector2({x, y});
    }
    setPosition(x, y);
}
void Move::setPosition(const float& x, const float& y) {
}
void Move::add_vertex(const Vector2& point) {
    m_vertices.push_back(point);
}
void Move::moveNext() {
    pointer = (pointer+1)%m_vertices.size();
}
void Move::moveBack() {
    pointer = (pointer-1)%m_vertices.size();
}

Vector2 Move::getPosition() const {
    return {0, 0};
}