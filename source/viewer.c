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
      error_code = parse_vertex(line, obj);
    } else if (*line == 'f' && *(line + 1) == ' ') {
      obj->edge_cnt++;
      error_code = parse_edge(line, obj);
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
 * @return OK/OBJ_VALUES_ERROR, int type
 */
int parse_vertex(char *ptr, obj_t *obj) {
  int error_code = OK;
  obj->vertices =
      (double **)realloc(obj->vertices, sizeof(double **) * obj->vertex_cnt);
  obj->vertices[obj->vertex_cnt - 1] = (double *)calloc(3, sizeof(double));
  ptr += 2;
  obj->vertices[obj->vertex_cnt - 1][0] = strtod(ptr, &ptr);
  if ((*ptr) != ' ') error_code = OBJ_VALUES_ERROR;
  obj->vertices[obj->vertex_cnt - 1][1] = strtod(ptr, &ptr);
  if ((*ptr) != ' ') error_code = OBJ_VALUES_ERROR;
  obj->vertices[obj->vertex_cnt - 1][2] = strtod(ptr, &ptr);
  return error_code;
}

/**
 * @brief Parses values ​of edges into a structure. Returns error
 * code 0 if values ​of edges are correct, otherwise - 2.
 *
 * @param ptr Pointer to line in obj.file, char pointer type
 * @param obj Struct, obj_t pointer type
 * @return OK/OBJ_VALUES_ERROR, int type
 */
int parse_edge(char *ptr, obj_t *obj) {
  int error_code = OK;
  obj->edges = (int **)realloc(obj->edges, sizeof(int **) * obj->edge_cnt);
  obj->edges[obj->edge_cnt - 1] = (int *)calloc(1, sizeof(int));
  int i = 0;
  while (strchr(ptr, ' ') != NULL && *ptr != '\0' && *ptr != 0) {
    i++;
    ptr = strchr(ptr, ' ');
    obj->edges[obj->edge_cnt - 1] =
        (int *)realloc(obj->edges[obj->edge_cnt - 1], sizeof(int) * i);
    obj->edges[obj->edge_cnt - 1][i - 1] = (int)strtol(ptr, &ptr, 10);
  }
  obj->edges[obj->edge_cnt - 1] =
      (int *)realloc(obj->edges[obj->edge_cnt - 1], sizeof(int) * (i + 1));
  obj->edges[obj->edge_cnt - 1][i] = 0;
  return error_code;
}

/**
 * @brief Creates obj_t structure.
 *
 * @param obj Struct, obj_t pointer type
 */
void init_obj(obj_t *obj, int vert, int edg) {
  obj->vertices = (double **)calloc(vert, sizeof(double **));
  obj->edges = (int **)calloc(edg, sizeof(int **));
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
      for (int i = 0; i < obj->vertex_cnt; i++) {
        if (obj->vertices[i]) free(obj->vertices[i]);
      }
      free(obj->vertices);
    }
    if (obj->edges) {
      for (int i = 0; i < obj->edge_cnt; i++) {
        if (obj->edges[i]) free(obj->edges[i]);
      }
      free(obj->edges);
    }
    obj = NULL;
  }
}
