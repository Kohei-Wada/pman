enum FIELD_ELEM {
    FIELD,
    WALL_V,
    WALL_H,
    KEEP_OUT,
    MAN,
    ENEMY,
    FOOD,
};


typedef struct {
    int x;
    int y;
    int vx;
    int vy;
}_MAN;


typedef struct {
    int x;
    int y;
    int vx;
    int vy;
    int type;
}_ENEM;
