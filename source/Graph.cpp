#include "../include/Graph.h"
#include "../include/Vertex.h"
#include "../include/General.h"
#include <cmath>
#include <string>

Graph::Graph(const int& index, FormSetting f_setting, const Vector2& window_size):
    Form(index, f_setting, window_size),
    track_graph_hover(&form_setting, &form_setting),
    graph_setting(&form_setting),
    setting_box(&form_setting),
    fixed_box(&form_setting, 0, m_mode),
    drag_box(&form_setting, 1, m_mode),
    collision_box(&form_setting, 2, m_mode)
{
    children.push_back(&track_graph_hover);
    children.push_back(&graph_setting); 

    setting_box.push_back(&fixed_box);
    setting_box.push_back(&drag_box);
    setting_box.push_back(&collision_box);

    fixed_box.setPosition(10, 5);
    fixed_box.setSize(100, 30);
    fixed_box.setText("Fixed");

    drag_box.setPosition(10, 40);
    drag_box.setSize(100, 30);
    drag_box.setText("Drag");

    collision_box.setPosition(10, 75);
    collision_box.setSize(100, 30);
    collision_box.setText("Collision");

    graph_setting.setPosition(-300, 100);
    graph_setting.setSize(300, 500);
    graph_setting.setText(0, "Settings");
    graph_setting.setText(1, "Insert Edge");
    graph_setting.setText(3, "Update Edge");
    graph_setting.setText(2, "Remove Edge");
    graph_setting.add_vertex({-300, 100});
    graph_setting.add_vertex({10, 100});
    graph_setting.setVisible(false);
    graph_setting.select(-1);

    setting_box.setSize(250, 110);
    setting_box.setPosition(graph_setting.getAutoSize().x + 15, 0);

    graph_setting.push_back(0, &setting_box);

    track_graph_hover.setSize(10, graph_setting.getAutoSize().y);
    track_graph_hover.setPosition(0, 100);
    track_graph_hover.setText("");

    chosen = -1;
    m_mode = 0;
};
string Graph::RandomCreate() const {
    srand(time(0));
    int n = rand()%20;
    string ans = to_string(n) + '\n';
    vector<vector<bool>> matrix(n, vector<bool>(n, 0));
    for (int i = rand()%20; i>=0; i--) {
        int row = rand()%n;
        int col = rand()%n;
        matrix[row][col] = 1;
        matrix[col][row] = 1;
    }
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            ans += to_string(matrix[i][j])+" ";
        }
        ans += '\n';
    }
    return ans;
}
void Graph::add(const vector<std::string>& values) {
    if (values.size()>1) {
        int n = to_int(values[0]);
        for (int i = 0; i<n; i++) {
            vertices.push_back(Vertex(&form_setting));
            vertices.back().setPosition(m_window_size.x/2, m_window_size.y/2);
            vertices.back().setSize(50, 50);;
            vertices.back().setValue(i);
        }
        for (int i = 0; i<n; i++) {
            for (int j = 0; j<n; j++) {
                int weight = to_int(values[i*n+j+1]);
                if (weight) {
                    edges.push_back(Edge(&vertices[i], &vertices[j]));
                }
            }
        }
    } else {
        vertices.push_back(Vertex(&form_setting));
        vertices.back().setPosition(m_window_size.x/2, m_window_size.y/2);
        vertices.back().setSize(50, 50);;
        vertices.back().setValue(to_int(values[0]));
    }
}
void Graph::draw() {
    for (int i = 0; i<edges.size(); i++) edges[i].draw();
    for (int i =0 ;i <vertices.size(); i++) vertices[i].draw();
    Form::draw();
}
void Graph::handle() {
    Form::handle();
    for (int i = 0; i<edges.size(); i++) edges[i].handle();
    for (int i = 0; i<vertices.size(); i++) {
        vertices[i].handle();
        if (vertices[i].isPressed()) vertices[i].start(0, RED, WHITE, 1);
        vertices[i].setFixed(m_mode == 0);
        vertices[i].setDragable(m_mode == 1);
        if (m_mode != 0) {
            Vector2 pos = vertices[i].getCenter();
            float radius = vertices[i].getRadius();
            Vector2 velocity = {0, 0}, acceleration = {0, 0};
            if (pos.x-radius<m_workspace.x)                             {
                acceleration.x = -vertices[i].getVelocity().x*1.8;
                vertices[i].setPosition(m_workspace.x + radius, pos.y);
            }
            else if (pos.x+radius>m_workspace.x + m_workspace.width)    {
                acceleration.x = - vertices[i].getVelocity().x*1.8;
                vertices[i].setPosition(m_workspace.x + m_workspace.width - radius, pos.y);
            }
            if (pos.y - radius<m_workspace.y)                           {
                acceleration.y = -vertices[i].getVelocity().y*1.8;
                vertices[i].setPosition(pos.x, m_workspace.y + radius);
            }
            else if (pos.y+radius > m_workspace.y + m_workspace.height) {
                acceleration.y = -vertices[i].getVelocity().y*1.8;
                vertices[i].setPosition(pos.x, m_workspace.y + m_workspace.height - radius);
            }
            vertices[i].add_acceleration(acceleration);

            for (int j = i+1; j<vertices.size(); j++) {
                if (abs(vertices[i].getCenter()-vertices[j].getCenter()) < vertices[i].getRadius() + vertices[j].getRadius()) {
                    Vector2 delta = vertices[j].getCenter() - vertices[i].getCenter();
                    delta = delta/abs(delta)*(vertices[i].getRadius() + vertices[j].getRadius() - abs(delta));
                    if (m_mode == 2) {
                        Vector2 velocityA = vertices[i].getVelocity();
                        Vector2 velocityB = vertices[j].getVelocity();
                        vertices[i].setVelocity(velocityB - delta/10);
                        vertices[j].setVelocity(velocityA + delta/10);
                    } else {
                        Vector2 posA = vertices[i].getPosition() - delta*1.1;
                        Vector2 posB = vertices[j].getPosition() + delta*1.1;
                        vertices[i].setPosition(posA.x, posA.y);
                        vertices[j].setPosition(posB.x, posB.y);
                    }
                }
            }
        }
    }

    if (track_graph_hover.isHovered()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = track_graph_hover.getPosition();
            pos.y += GetMouseDelta().y;
            track_graph_hover.setPosition(pos.x, pos.y);
            pos = graph_setting.getPosition();
            pos.y += GetMouseDelta().y;
            graph_setting.setPosition(pos.x, pos.y);
        }
        if (graph_setting.getVertexDone() == 0) {
            graph_setting.setVisible(true);
            graph_setting.next();
        }
    }
    else if (!graph_setting.isHovered()) {
        if (graph_setting.getVertexDone() == 0)
            graph_setting.setVisible(false);
        else if (graph_setting.getVertexDone() == 1) {
            graph_setting.next();
            graph_setting.select(-1);
        }
    }
}
Graph::~Graph() {
    
}