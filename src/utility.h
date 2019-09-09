#ifndef EOF_UTILITY_H
#define EOF_UTILITY_H

int eof_folder_exists(const char * dir);	//Returns nonzero if the specified file path exists and is a directory
int eof_chdir(const char * dir);		//Changes the current working directory of the program.  Returns nonzero on error
int eof_mkdir(const char * dir);
int eof_system(const char * command);	//Runs the specified system command, after reformatting the command string accordingly

void *eof_buffer_file(const char * fn, char appendnull);
	//Loads the specified file into a memory buffer and returns the buffer, or NULL upon error
	//If appendnull is nonzero, an extra 0 byte is written at the end of the buffer, potentially necessary if buffering a file that will be read as text, ensuring the buffer is NULL terminated
int eof_copy_file(const char * src, const char * dest);	//Copies the source file to the destination file.  Returns 0 upon error
int eof_file_compare(char *file1, char *file2);	//Returns zero if the two files are the same

int eof_check_string(char * tp);	//Returns nonzero if the string contains at least one non space ' ' character before it terminates

//Unicode font handling stuff
extern unsigned short * eof_ucode_table;						//Stores Unicode mappings for the 256 extended ASCII characters, some of which are set to 0x20 for nonprintable characters
void eof_allocate_ucode_table(void);							//Populates the contents of eof_ucode_table[]
void eof_free_ucode_table(void);								//Frees eof_ucode_table[]
int eof_convert_from_extended_ascii(char * buffer, int size);	//Convert a string from 8-bit ASCII to the current format
int eof_convert_to_extended_ascii(char * buffer, int size);		//Convert a string from the current format to 8-bit ASCII
int eof_lookup_extended_ascii_code(int character);
	//Accepts an input UTF-8 character and returns the matching extended ASCII code from eof_ucode_table[] if it exists
	//Returns 0 if there is no match or upon error
int rs_lyric_substitute_char_utf8(int character, int function);
	//Converts the input UTF-8 character into extended ASCII and uses rs_lyric_substitute_char_extended() to search for an applicable normal ASCII substitution
	//  for example, replacing an accented A character with a non-accented version.
	//If function is 0, substitutions are sought for any accented Latin character
	//If function is 1, substitutions are only sought for characters that Rocksmith doesn't support
	//If no substitution is found, the input character is returned unchanged

int eof_string_has_non_ascii(char *str);	//Returns nonzero if any characters in the UTF-8 encoded string have non ASCII characters (any character valued over 127)
int eof_string_has_non_alphanumeric(char *str);	//Returns nonzero if any characters in the UTF-8 encoded string have non alphanumeric ASCII characters
void eof_sanitize_string(char *str);		//Replaces any non-printable or non ASCII (characters numbered higher than 127) characters with spaces
int eof_char_is_hex(int c);
	//Returns nonzero if c is a numerical digit or an upper/lower case letter A, B, C, D, E or F
int eof_string_is_hexadecimal(char *string);
	//Returns nonzero if all characters in the provided string are hexadecimal characters
	//Returns 0 on error

int eof_is_illegal_filename_character(char c);	//Returns nonzero if the specified character is not legal for use in a filename in Windows

int eof_remake_color(int hexrgb);	//Accepts a color in hexadecimal RGB format and returns the result of makecol() passed each relevant byte

PACKFILE *eof_pack_fopen_retry(const char *filename, const char *mode, unsigned count);
	//Attempts to open the specified file in the specified mode up to [count] number of times, with a 1ms delay between each attempt
	//If any attempts succeed, the PACKFILE handle is returned, otherwise if all attempts fail, NULL is returned

int eof_number_is_power_of_two(unsigned long value);
	//Returns nonzero if the specified value is any power of two from 2^0 through 2^31

#endif
