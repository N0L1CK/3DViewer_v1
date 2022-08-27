#include "../header/viewer.h"

/**
 * @brief X-axis vertex shift.
 *
 * @param obj Struct, obj_t pointer type
 * @param value Value of shift, float type
 */
void move_x(obj_t* obj, float value) {
  for (int i = 0; i < obj->vertex_cnt; i++) {
    obj->vertices[i][0] += value;
  }
}

/**
 * @brief Y-axis vertex shift.
 *
 * @param obj Struct, obj_t pointer type
 * @param value Value of shift, float type
 */
void move_y(obj_t* obj, float value) {
  for (int i = 0; i < obj->vertex_cnt; i++) {
    obj->vertices[i][1] += value;
  }
}

/**
 * @brief Z-axis vertex shift.
 *
 * @param obj Struct, obj_t pointer type
 * @param value Value of shift, float type
 */
void move_z(obj_t* obj, float value) {
  for (int i = 0; i < obj->vertex_cnt; i++) {
    obj->vertices[i][2] += value;
  }
}

/**
 * @brief Rotates the vertex along the x-axis.
 * X' = X
 * Y' = Y*cos(a) + Z*sin(a)
 * Z':=-Y*sin(a) + Z*cos(a)
 * @param obj Struct, obj_t pointer type
 * @param angle Coefficient of scaling, float type
 */
void rotate_x(obj_t* obj, float angle) {
  for (int i = 0; i < obj->vertex_cnt; i++) {
    double y = obj->vertices[i][1];
    double z = obj->vertices[i][2];
    obj->vertices[i][1] = y * cos(angle) - z * sin(angle);
    obj->vertices[i][2] = y * sin(angle) + z * cos(angle);
  }
}

/**
 * @brief Rotates the vertex along the y-axis.
 * X' = X*cos(a) - Z*sin(a)
 * Y' = Y
 * Z':= X*sin(a) + Z*cos(a)
 * @param obj Struct, obj_t pointer type
 * @param angle Coefficient of scaling, float type
 */
void rotate_y(obj_t* obj, float angle) {
  for (int i = 0; i < obj->vertex_cnt; i++) {
    double x = obj->vertices[i][0];
    double z = obj->vertices[i][2];
    obj->vertices[i][0] = x * cos(angle) + z * sin(angle);
    obj->vertices[i][2] = -x * sin(angle) + z * cos(angle);
  }
}

/**
 * @brief Rotates the vertex along the z-axis.
 * X' = X*cos(a) + Y*sin(a)
 * Y' =-X*sin(a) + Y*cos(a)
 * Z':= Z
 * @param obj Struct, obj_t pointer type
 * @param angle Coefficient of scaling, float type
 */
void rotate_z(obj_t* obj, float angle) {
  for (int i = 0; i < obj->vertex_cnt; i++) {
    double x = obj->vertices[i][0];
    double y = obj->vertices[i][1];
    obj->vertices[i][0] = x * cos(angle) - y * sin(angle);
    obj->vertices[i][1] = x * sin(angle) + y * cos(angle);
  }
}

/**
 * @brief Scale vertex by coefficient ratio.
 *
 * @param obj Struct, obj_t pointer type
 * @param ratio Coefficient of scaling, float type
 */
void scale(obj_t* obj, float ratio) {
  if (ratio > 0) {
    for (int row = 0; row < obj->vertex_cnt; row++) {
      for (int col = 0; col < 3; col++) {
        obj->vertices[row][col] *= ratio;
      }
    }
  }
}
