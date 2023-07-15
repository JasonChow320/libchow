#include "csv_reader.h"

/**
 * @brief Initalize the csv reader struct by reading the csv file and 
 *        initalizing the internal states
 *
 * @param reader               the csv_reader struct to initailize
 * @param fp                   the file stream that csv reader will read from
 * @param buffer               the buffer to save the csv file to
 * @param buffer_size          the buffer size passed into buffer
 * @param num_record_fields    the number of fields per record in the csv
 *
 * @return 1 if successfully initailized, 0 otherwise
 */
enum csv_reader_rc csv_reader_init(struct csv_reader *reader, 
                                   FILE *fp, 
                                   char *buffer, 
                                   size_t buffer_size, 
                                   uint32_t num_record_fields)
{
    if (fp == NULL) {
        return CSV_READER_RC_INVALID_ARGUMENTS;
    }
}

/**
 * @brief Get the next csv record from the csv_reader struct passed in
 * 
 * @param reader    the csv_reader struct to parse out csv record from
 *
 * @return 1 if a record is able to be parsed, 0 otherwise
 */
int csv_reader_get_next_record(struct csv_reader *reader);

/**
 * @brief Get a field by index from the current loaded record in the csv reader
 * 
 * @param reader    the csv_reader struct to parse out csv record from
 * @param idx       the index of the field in the record to get
 *
 * @return pointer to field string if a record is able to be parsed, otherwise
 *         null if be returned
 */
char* csv_reader_get_field_by_idx(struct csv_reader *reader, size_t idx);
