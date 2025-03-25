#include "../include/Edge.h"
#include "../include/General.h"
#include <cmath>
Edge::Edge(Vertex* start, Vertex* end) {
    m_start = start;
    m_end = end;
}
void Edge::draw() {
    DrawLineEx(m_start->getCenter(), m_end->getCenter(), 2, WHITE);
}
void Edge::handle() {
    Vector2 delta = m_end->getCenter() - m_start->getCenter();
    float dis = abs(m_start->getCenter() - m_end->getCenter());
    if (dis < 200) {
        delta = delta/dis*std::sqrt(200 - dis);
        m_start->add_acceleration(-1*delta);
        m_end->add_acceleration(delta);
    } 
    else if (dis > 400) {
        delta = delta/dis*std::sqrt(dis - 400);
        m_start->add_acceleration(delta);
        m_end->add_acceleration(-1*delta);
    }
}