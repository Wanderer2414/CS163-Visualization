#include "../include/Graph.h"
#include "../include/IncludePath.h"
#include "../include/General.h"

Graph::Graph(const int& index, FormSetting f_setting, const Vector2& window_size):
    Form(index, f_setting, window_size),
    track_graph_hover(&form_setting, &form_setting),
    graph_setting(&form_setting),
    setting_box(&form_setting),
    fixed_choice(&form_setting, 0, m_mode),
    drag_choice(&form_setting, 1, m_mode),
    collision_choice(&form_setting, 2, m_mode),
    weight_choice(&form_setting, 0, m_weight),
    unweight_choice(&form_setting, 1,m_weight),
    direct_choice(&form_setting, 0, m_type),
    undirect_choice(&form_setting, 1, m_type),

    dfs_choice(&form_setting, 0, search_type),
    bfs_choice(&form_setting, 1, search_type),

    search_graph_box(&form_setting),
    tools_box(&form_setting),
    
    extract_box(&form_setting),
    extract_text_bx(&form_setting, &form_setting),
    pull_matrix_button(&form_setting, &form_setting),

    vertex_label(&form_setting),
    edge_label(&form_setting),
    vertex_textbox(&form_setting, &form_setting),
    edge_textbox(&form_setting, &form_setting),

    color_pointer(0)
{
    children.push_back(&track_graph_hover);
    children.push_back(&graph_setting); 

    setting_box.push_back(&fixed_choice);
    setting_box.push_back(&drag_choice);
    setting_box.push_back(&collision_choice);

    setting_box.push_back(&weight_choice);
    setting_box.push_back(&unweight_choice);

    setting_box.push_back(&direct_choice);
    setting_box.push_back(&undirect_choice);

    tools_box.push_back(&match_tool);

    extract_box.push_back(&extract_text_bx);
    extract_box.push_back(&pull_matrix_button);

    search_graph_box.push_back(&dfs_choice);
    search_graph_box.push_back(&bfs_choice);

    //Setting box controller
    fixed_choice.setPosition(10, 5);
    fixed_choice.setSize(100, 30);
    fixed_choice.setText("Fixed");

    drag_choice.setPosition(10, 40);
    drag_choice.setSize(100, 30);
    drag_choice.setText("Drag");

    collision_choice.setPosition(10, 75);
    collision_choice.setSize(100, 30);
    collision_choice.setText("Collision");

    weight_choice.setPosition(170, 5);
    weight_choice.setSize(100, 30);
    weight_choice.setText("Weight");

    unweight_choice.setPosition(170, 40);
    unweight_choice.setSize(100, 30);
    unweight_choice.setText("Unweight");

    direct_choice.setPosition(170, 85);
    direct_choice.setSize(100, 30);
    direct_choice.setText("Direct");

    undirect_choice.setPosition(170, 120);
    undirect_choice.setSize(100, 30);
    undirect_choice.setText("Undirect");

    //Tool controller
    match_tool.setButtonStage(0, match_icon, match_filled_icon);
    match_tool.setPosition(5, 5);
    match_tool.setSize(40, 40);

    //Extract controller
    extract_text_bx.setPosition(5, 5);
    extract_text_bx.setSize(290, 145);
    extract_text_bx.setAlignText(TextBox::Top | TextBox::Left);

    pull_matrix_button.setPosition(5, 155);
    pull_matrix_button.setSize(290, 40);
    pull_matrix_button.setText("Pull");

    //Graph setting
    graph_setting.setPosition(-300, 100);
    graph_setting.setSize(300, 500);
    graph_setting.setText(0, "Settings");
    graph_setting.setText(1, "Tools");
    graph_setting.setText(2, "Algorithms");
    graph_setting.setText(3,"Extract");
    graph_setting.add_vertex({-300, 100});
    graph_setting.add_vertex({10, 100});
    graph_setting.setVisible(false);
    graph_setting.select(-1);

    setting_box.setSize(340, 170);
    setting_box.setPosition(graph_setting.getAutoSize().x + 15, 0);

    tools_box.setSize(200, 50);
    tools_box.setPosition(graph_setting.getAutoSize().x + 15, 45);

    extract_box.setPosition(graph_setting.getAutoSize().x+15, 5);
    extract_box.setSize(300, 200);
    
    graph_setting.push_back(0, &setting_box);   
    graph_setting.push_back(1, &tools_box);
    graph_setting.push_back(3, &extract_box);

    track_graph_hover.setSize(10, graph_setting.getAutoSize().y);
    track_graph_hover.setPosition(0, 100);
    track_graph_hover.setText("");

    //Search box controller
    dfs_choice.setSize(100, 30);
    dfs_choice.setPosition(15, 5);
    dfs_choice.setText("Depth first search");

    bfs_choice.setSize(200, 30);
    bfs_choice.setPosition(15, 50);
    bfs_choice.setText("Breath first search");

    search_graph_box.setPosition(option_box.getAutoSize().x + 15, 30);
    search_graph_box.setSize(search_box.getSize().x, 100);
    option_box.push_back(3, &search_graph_box);

    //ReSetting console
    console_setting.font = LoadFont(font_link);
    console_setting.font_size = 20;
    console_setting.spacing = 2;
    console_setting.color = BLACK;
    console.text_setting = &console_setting;

    //Add random button to create box
    vertex_label.setText("V: ");
    vertex_label.setPosition(5, 35);
    vertex_label.setSize(30, 40);
    vertex_label.setAlignText(Label::Left | Label::Center);

    vertex_textbox.setPosition(40, 35);
    vertex_textbox.setSize(65, 40);
    vertex_textbox.setAlignText(TextBox::Left | TextBox::Center);

    random_vertex_button.setPosition(110, 40);
    random_vertex_button.setSize(30, 30);
    random_vertex_button.setButtonStage(0, Rand, Rand);

    edge_label.setText("E: ");
    edge_label.setPosition(160, 35);
    edge_label.setSize(30, 40);

    edge_textbox.setPosition(195, 35);
    edge_textbox.setSize(65, 40);
    edge_textbox.setAlignText(TextBox::Left | TextBox::Center);

    random_edge_button.setPosition(265, 40);
    random_edge_button.setSize(30, 30);
    random_edge_button.setButtonStage(0, Rand, Rand);
    
    create_textbox.setPosition(5, 80);
    create_button.setPosition(5, 190);

    create_box.push_back(&edge_label);
    create_box.push_back(&edge_textbox);
    create_box.push_back(&random_edge_button);
    create_box.push_back(&vertex_label);
    create_box.push_back(&vertex_textbox);
    create_box.push_back(&random_vertex_button);
    create_box.setSize(310, 240);
    create_box.reLocate(&create_textbox);
    create_box.reLocate(&create_button);

    chosen = -1;
    m_mode = 2;
    m_weight = 1;
    m_type = 1;
    m_tool = -1;
    m_is_lock = false;
    search_type = 0;
};

void Graph::draw() {
    for (int i = 0; i<true_edges.size(); i++) {
        true_edges[i]->draw();
    }
    if (m_type == 0) {
        for (int i = 0; i<reverse_edge.size(); i++) reverse_edge[i]->draw();
    }
    for (int i =0 ;i <vertices.size(); i++) vertices[i]->draw();
    Form::draw();

    if (m_tool!=-1) 
        DrawTexture(cursor_icon, GetMousePosition().x, GetMousePosition().y-cursor_icon.height, WHITE);
}
void Graph::handle() {
    Form::handle();
    for (int i = 0; i<true_edges.size(); i++) {
        true_edges[i]->handle();
        true_edges[i]->setMode(m_weight == 0);
        //Check edge color change 
        if (true_edges[i]->IsColorChange() && !m_is_lock) {
            if (!true_edges[i]->IsReverse()) {
                float angular = arctan(true_edges[i]->m_start->getCenter() - true_edges[i]->m_end->getCenter());
                true_edges[i]->m_end->start(angular, true_edges[i]->start_color, true_edges[i]->m_end->getColor());
            } else {
                float angular = arctan(true_edges[i]->m_end->getCenter() - true_edges[i]->m_start->getCenter());
                true_edges[i]->m_start->start(angular, true_edges[i]->end_color, true_edges[i]->m_start->getColor());
            }
        }
        //Vertex color change
        if (!m_is_lock && true_edges[i]->m_start->IsColorChange() && (true_edges[i]->m_start->getColor() != true_edges[i]->start_color)) {
            true_edges[i]->start(false, false);
        }
        if (m_type == 1) {
            if (!m_is_lock && true_edges[i]->m_end->IsColorChange() && (true_edges[i]->m_end->getColor() != true_edges[i]->start_color)) {
                true_edges[i]->start(true, false);
            }
        }
    }
    //Check reverse color change
    if (m_type == 0) {
        for (int i = 0; i<reverse_edge.size(); i++) {
            reverse_edge[i]->handle();
            reverse_edge[i]->setMode(m_weight == 0);
            if (!m_is_lock && reverse_edge[i]->IsColorChange()) {
                if (!reverse_edge[i]->IsReverse()) {
                    float angular = arctan(reverse_edge[i]->m_start->getCenter() - reverse_edge[i]->m_end->getCenter());
                    reverse_edge[i]->m_end->start(angular, reverse_edge[i]->start_color, reverse_edge[i]->m_end->getColor());
                }
            }
            //Check vertex change color
            if (!m_is_lock && reverse_edge[i]->m_start->IsColorChange() && (reverse_edge[i]->m_start->getColor() != reverse_edge[i]->start_color)) {
                reverse_edge[i]->start(false, false);
            }
        }
    }
    bool isFocus = false;
    for (int i = 0; i<vertices.size(); i++) {
        vertices[i]->handle();
        vertices[i]->setFixed(m_mode == 0);
        vertices[i]->setDragable(m_mode == 1);

        //Match vertex
        if (vertices[i]->isFocused()) {
            isFocus = true;
            if (chosen == -1) chosen = i;
            else if (chosen != i) {
                if (m_tool == 0) add_edge(chosen, i, 1);
                chosen = i;
            }
        }
        //Check out window
        if (m_mode != 0) {
            Vector2 pos = vertices[i]->getCenter();
            float radius = vertices[i]->getRadius();
            Vector2 velocity = {0, 0}, acceleration = {0, 0};
            if (pos.x-radius<m_workspace.x)                             {
                acceleration.x = -vertices[i]->getVelocity().x*1.8;
                vertices[i]->setPosition(m_workspace.x + radius, pos.y);
            }
            else if (pos.x+radius>m_workspace.x + m_workspace.width)    {
                acceleration.x = - vertices[i]->getVelocity().x*1.8;
                vertices[i]->setPosition(m_workspace.x + m_workspace.width - radius, pos.y);
            }
            if (pos.y - radius<m_workspace.y)                           {
                acceleration.y = -vertices[i]->getVelocity().y*1.8;
                vertices[i]->setPosition(pos.x, m_workspace.y + radius);
            }
            else if (pos.y+radius > m_workspace.y + m_workspace.height) {
                acceleration.y = -vertices[i]->getVelocity().y*1.8;
                vertices[i]->setPosition(pos.x, m_workspace.y + m_workspace.height - radius);
            }
            vertices[i]->add_acceleration(acceleration);
            //Check collision
            for (int j = i+1; j<vertices.size(); j++) {
                if (abs(vertices[i]->getCenter()-vertices[j]->getCenter()) < vertices[i]->getRadius() + vertices[j]->getRadius()) {
                    Vector2 delta = vertices[j]->getCenter() - vertices[i]->getCenter();
                    delta = delta/abs(delta)*(vertices[i]->getRadius() + vertices[j]->getRadius() - abs(delta));
                    if (m_mode == 2) {
                        Vector2 velocityA = vertices[i]->getVelocity();
                        Vector2 velocityB = vertices[j]->getVelocity();
                        vertices[i]->setVelocity(velocityB - delta/10);
                        vertices[j]->setVelocity(velocityA + delta/10);
                    } else {
                        Vector2 posA = vertices[i]->getPosition() - delta*1.1;
                        Vector2 posB = vertices[j]->getPosition() + delta*1.1;
                        vertices[i]->setPosition(posA.x, posA.y);
                        vertices[j]->setPosition(posB.x, posB.y);
                    }
                }
            }
        }
    }

    //Change type
    if (direct_choice.isChanged() && direct_choice.isPressed()) {
        for (int i = 0; i<true_edges.size(); i++) {
            true_edges[i]->setType(true);
        }
        for (int i = 0; i<reverse_edge.size(); i++) {
            int row = reverse_edge[i]->m_start->getIndex();
            int col = reverse_edge[i]->m_end->getIndex();
            if (matrix[col][row]!=-1)
                reverse_edge[i]->setColor(true_edges[matrix[col][row]]->start_color);
        }
    } else if (undirect_choice.isChanged() && undirect_choice.isPressed()) {
        for (int i = 0; i<true_edges.size(); i++) {
            true_edges[i]->setType(false);
            if (true_edges[i]->start_color != true_edges[i]->m_end->getColor()) 
                true_edges[i]->start(true, false);
        }
    }
    if (!isFocus) chosen = -1;
    //Graph box show
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
    //Insert edge/ Match tool press
    if (match_tool.isPressed()) {
        if (m_tool == -1) {
            m_tool = 0;
            HideCursor();
            cursor_icon = LoadTexture(match_cursor_icon);
            cursor_icon.width = cursor_icon.height = 30;
        }
        else {
            ShowCursor();
            UnloadTexture(cursor_icon);
            m_tool = -1;
        }
    }
    //Random create
    if (random_edge_button.isPressed()) {
        edge_textbox.setText(to_string(rand()%20));
    }
    if (random_vertex_button.isPressed()) {
        vertex_textbox.setText(to_string(rand()%20));
    }
    //Matrix pull
    if (pull_matrix_button.isPressed()) {
        pull_matrix();
    }
}