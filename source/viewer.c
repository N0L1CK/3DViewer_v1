#include "../header/viewer.h"

/**
 * @brief Opens and reads .obj file. Returns error code 0 if filename is
 * correct, otherwise - 1.
 *
 * @param path Path to .obj file, const char pointer type
 * @param obj Struct, obj_t pointer type
 * @return OK/FILENAME_ERROR, int type
 */
int open_file(const char *path, obj_t *obj) {
  int error_code = OK;
  char file[LENGTH] = {0};
  snprintf(file, sizeof(file), "%s", path);
  FILE *fp = fopen(file, "rt");
  if (fp) {
    error_code = parse_obj(fp, obj);
    fclose(fp);
  } else {
    error_code = FILENAME_ERROR;
  }
  return error_code;
}

/**
 * @brief Parses values ​​from .obj file into a structure. Returns error
 * code 0 if values in file are correct, otherwise - 2.
 *
 * @param fp FILE pointer type
 * @param obj Struct, obj_t pointer type
 * @return OK/OBJ_VALUES_ERROR, int type
 */
int parse_obj(FILE *fp, obj_t *obj) {
  int error_code = OK;
  char line[LENGTH] = {0};
  while (fgets(line, LENGTH, fp) && error_code == OK) {
    if (*line == 'v' && *(line + 1) == ' ') {
      obj->vertex_cnt++;
    } else if (*line == 'f' && *(line + 1) == ' ') {
      obj->edge_cnt++;
    }
  }
  obj->vertices =
      (double *)realloc(obj->vertices, sizeof(double *) * obj->vertex_cnt * 3);
  obj->edges = (int *)realloc(obj->edges, sizeof(int *) * obj->edge_cnt * 6);
  if (obj->vertices && obj->edges) {
    fseek(fp, 0, SEEK_SET);
    int v_cnt = obj->vertex_cnt;
    int e_cnt = obj->edge_cnt;
    while (fgets(line, LENGTH, fp) && error_code == OK) {
      if (*line == 'v' && *(line + 1) == ' ') {
        error_code = parse_vertex(line, obj, v_cnt);
        v_cnt--;
      } else if (*line == 'f' && *(line + 1) == ' ') {
        error_code = parse_edge(line, obj, e_cnt);
        e_cnt--;
      }
    }
  }
  *line = '\0';
  return error_code;
}

/**
 * @brief Parses values ​of vertex into a structure. Returns error
 * code 0 if values ​of vertex are correct, otherwise - 2.
 *
 * @param ptr Pointer to line in obj.file, char pointer type
 * @param obj Struct, obj_t pointer type
 * @param v_cnt Shift of index in array of vertecies, int type
 * @return OK/OBJ_VALUES_ERROR, int type
 */
int parse_vertex(char *ptr, obj_t *obj, int v_cnt) {
  int error_code = OK;
  ptr += 2;
  obj->vertices[(obj->vertex_cnt - v_cnt) * 3] = strtod(ptr, &ptr);
  if ((*ptr) != ' ') error_code = OBJ_VALUES_ERROR;
  obj->vertices[(obj->vertex_cnt - v_cnt) * 3 + 1] = strtod(ptr, &ptr);
  if ((*ptr) != ' ') error_code = OBJ_VALUES_ERROR;
  obj->vertices[(obj->vertex_cnt - v_cnt) * 3 + 2] = strtod(ptr, &ptr);
  return error_code;
}

/**
 * @brief Parses values ​of edges into a structure. Returns error
 * code 0 if values ​of edges are correct, otherwise - 2.
 *
 * @param ptr Pointer to line in obj.file, char pointer type
 * @param obj Struct, obj_t pointer type
 * @param e_cnt Shift of index in array of edges, int type
 * @return OK/OBJ_VALUES_ERROR, int type
 */
int parse_edge(char *ptr, obj_t *obj, int e_cnt) {
  int error_code = OK;
  if (strchr(ptr, ' ') == NULL) error_code = OBJ_VALUES_ERROR;
  ptr = strchr(ptr, ' ');
  int first_index = (int)strtol(ptr, &ptr, 10) - 1;
  obj->edges[(obj->edge_cnt - e_cnt) * 6] = first_index;
  if (strchr(ptr, ' ') == NULL) error_code = OBJ_VALUES_ERROR;
  ptr = strchr(ptr, ' ');
  int second_index = (int)strtol(ptr, &ptr, 10) - 1;
  obj->edges[(obj->edge_cnt - e_cnt) * 6 + 1] = second_index;
  obj->edges[(obj->edge_cnt - e_cnt) * 6 + 2] = second_index;
  if (strchr(ptr, ' ') == NULL) error_code = OBJ_VALUES_ERROR;
  ptr = strchr(ptr, ' ');
  int third_index = (int)strtol(ptr, &ptr, 10) - 1;
  obj->edges[(obj->edge_cnt - e_cnt) * 6 + 3] = third_index;
  obj->edges[(obj->edge_cnt - e_cnt) * 6 + 4] = third_index;
  obj->edges[(obj->edge_cnt - e_cnt) * 6 + 5] = first_index;
  return error_code;
}

/**
 * @brief Creates obj_t structure.
 *
 * @param obj Struct, obj_t pointer type
 */
void init_obj(obj_t *obj, int vertex_cnt, int edge_cnt) {
  obj->vertices = (double *)calloc(vertex_cnt, sizeof(double *));
  obj->edges = (int *)calloc(edge_cnt, sizeof(int *));
  obj->vertex_cnt = 0;
  obj->edge_cnt = 0;
}

/**
 * @brief Removes obj_t structure.
 *
 * @param obj Struct, obj_t pointer type
 */
void clean_obj(obj_t *obj) {
  if (obj) {
    if (obj->vertices) {
      free(obj->vertices);
    }
    if (obj->edges) {
      free(obj->edges);
    }
    obj = NULL;
  }
}
