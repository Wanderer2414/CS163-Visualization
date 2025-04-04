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
void Move::handle() {
    if (progress != pointer) {
        Vector2 delta = m_vertices[pointer] - getPosition();
        if (abs(pointer-progress)>0.1) {
            Vector2 pos = getPosition() + delta/10;
            progress += (pointer-progress)/10;
            setPosition(pos.x, pos.y);
        } else {
            setPosition(m_vertices[pointer].x, m_vertices[pointer].y);
            progress = pointer;
        }
    }
}
void Move::setPosition(const float& x, const float& y) {
    if (progress == pointer) {
        for (int i = 0; i<m_vertices.size(); i++) {
            m_vertices[i] = m_vertices[i] - getPosition() + Vector2({x, y});
        }
    }
}
void Move::add_vertex(const Vector2& point) {
    m_vertices.push_back(point);
}
void Move::next() {
    pointer++;
    if (pointer == m_vertices.size()) pointer = 0;
}
void Move::back() {
    pointer--;
    if (!pointer) pointer = m_vertices.size()-1;
}

Vector2 Move::getPosition() const {
    return {0, 0};
}