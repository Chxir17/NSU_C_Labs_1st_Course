#include "structs.h"
#include "encoder.h"
#include "decoder.h"

int main() {
    Data *data = malloc(sizeof(Data));
    if (data == NULL) {
        return 0;
    }
    data->bitpos = 0;
    data->pos = 0;
    data->size = 0;
    data->file = fopen("in.txt", "rb");
    if (data->file != NULL) {
        char mode;
        if (fread(&mode, 1, 1, data->file) == 0) {
            fclose(data->file);
            free(data);
            return 0;
        }
        if (mode == 'c') {
            encode(data);
        }
        else {
            decode(data);
        }
        fclose(data->file);
    }
    free(data);
    return 0;
}
