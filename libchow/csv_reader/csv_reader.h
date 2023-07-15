#ifndef CSV_READER_H
#define CSV_READER_H

#include <stdio.h>
#include <stdint.h>

struct csv_reader {
    char *csv_buffer;
    size_t csv_buffer_size;
    size_t csv_file_content_len;

    size_t buffer_cursor;
    size_t num_record_fields;
};

enum csv_reader_rc {
    CSV_READER_RC_INVALID_ARGUMENTS = -1,
    CSV_READER_RC_SUCCESS,
    CSV_READER_RC_NO_RECORD,
};

enum csv_reader_rc csv_reader_init(struct csv_reader *reader, FILE *fp, char *buffer, size_t buffer_size, uint32_t num_record_fields);
enum csv_reader_rc csv_reader_get_next_record(struct csv_reader *reader);
char* csv_reader_get_field_by_idx(struct csv_reader *reader, size_t idx);

#endif
