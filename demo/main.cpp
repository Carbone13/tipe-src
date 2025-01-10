#include "main.hpp"

RTree tree;

Item ITEMS[ITEM_COUNT];

void init() {
  srand(136399342);
  for (int i = 0; i < ITEM_COUNT; i++) {
    ITEMS[i].id = i + 1;
    ITEMS[i].x = rand() % (WIDTH - 50) + 30;
    ITEMS[i].y = rand() % (HEIGHT - 30) + 10;
  }
}

void draw_tree_rec(App* s, Node* node, int depth = 0) {

  if (node->kind == LEAF) {
    draw_rect(s, node->mbr.a_x, node->mbr.a_y, node->mbr.b_y - node->mbr.a_y,
              node->mbr.b_x - node->mbr.a_x, 0, 0, 0);
  }
  if (node->kind == BRANCH) {
    for (int i = 0; i < node->count; i++) {
      draw_tree_rec(s, node->children[i], depth + 1);
    }
  }
}
void draw(App* s) {
  for (int i = 0; i < ITEM_COUNT; i++) {
    draw_circle(s, ITEMS[i].x, ITEMS[i].y, 1.f);
  }

  draw_tree_rec(s, tree.root);
}

int main() {
  App* s = create_application();
  init();

  tree.root->mbr = Rect(ITEMS[0].x, ITEMS[0].y, ITEMS[0].x, ITEMS[0].y);
  for (int i = 0; i < ITEM_COUNT; i++) {
    tree.insert(ITEMS[i]);
  }

  run(s, draw);

  return 0;
}
