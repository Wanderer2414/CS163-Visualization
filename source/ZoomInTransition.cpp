#include "../include/ZoomInTransition.h"
#include "../include/General.h"
float ZoomInTransition::getProgress() const {
    return percent;
}
void ZoomInTransition::handle() {
    if (percent < 1 && clock.get()) {
        percent *= 1.07;
        if (percent>1) percent = 1;
        Vector2 pos = start_pos + delta*percent;
        Vector2 size = start_size + delta_size*percent;
        pos = pos - size/2;
        color.a = percent*255;
        host->setPosition(pos.x, pos.y);
        host->setSize(size.x, size.y);
    } else color.a = 0;
}
void ZoomInTransition::draw() {
    if (host) DrawRectangleV(host->getPosition(), host->getSize(), color);
}
void ZoomInTransition::start() {
    percent = 0.001;
    delta = m_position - host->getPosition() - host->getSize()/2;
    start_pos = host->getPosition() + host->getSize()/2;
    start_size = host->getSize();
    delta_size = m_size - host->getSize();
}