/* ################################################################### */
/* Copyright 2015 - Pierre Gentile                                     */
/*                                                                     */
/* This Software is licensed under the GPL licensed Version 2,         */
/* please read http://www.gnu.org/copyleft/gpl.html                    */
/*                                                                     */
/* you can redistribute it and/or modify it under the terms of the GNU */
/* General Public License as published by the Free Software            */
/* Foundation; either version 2 of the License.                        */
/*                                                                     */
/* This software is distributed in the hope that it will be useful,    */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of      */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   */
/* General Public License for more details.                            */
/* ################################################################### */

typedef struct charsetinfo_s charsetinfo_t;
typedef struct langinfo_s langinfo_t;
typedef struct ll_node_s ll_node_t;
typedef struct ll_s ll_t;
typedef struct term_s term_t;
typedef struct tst_node_s tst_node_t;
typedef struct toggle_s toggle_t;
typedef struct win_s win_t;
typedef struct word_s word_t;
typedef struct txt_attr_s txt_attr_t;
typedef struct limits_s limits_t;
typedef struct sed_s sed_t;
typedef struct interval_s interval_t;

void help(win_t * win, term_t * term, int last_line);
void short_usage(void);
void usage(void);

void *xmalloc(size_t size);
void *xcalloc(size_t num, size_t size);
void *xrealloc(void *ptr, size_t size);

interval_t *interval_new(void);
int interval_comp(void *a, void *b);
void interval_swap(void *a, void *b);

int ll_append(ll_t * const list, void *const data);
int ll_prepend(ll_t * const list, void *const data);
void ll_insert_before(ll_t * const list, ll_node_t * node, void *const data);
void ll_insert_after(ll_t * const list, ll_node_t * node, void *const data);
ll_node_t *ll_partition(ll_node_t * l, ll_node_t * h,
                        int (*comp) (void *, void *),
                        void (*swap) (void *, void *));
void ll_quicksort(ll_node_t * l, ll_node_t * h,
                  int (*comp) (void *, void *), void (*swap) (void *a, void *));
void ll_sort(ll_t * list, int (*comp) (void *, void *),
             void (*swap) (void *a, void *));
int ll_delete(ll_t * const list, ll_node_t * node);
ll_node_t *ll_find(ll_t * const, void *const,
                   int (*)(const void *, const void *));
void ll_init(ll_t * list);
ll_node_t *ll_new_node(void);
ll_t *ll_new(void);

int my_stricmp(const char *str1, const char *str2);

int isprint7(int i);
int isprint8(int i);

int count_leading_set_bits(unsigned char c);
int get_cursor_position(int *const r, int *const c);
void get_terminal_size(int *const r, int *const c);
char *mb_strprefix(char *d, char *s, int n, int *pos);
int mb_strlen(char *str);
wchar_t *mb_strtowcs(char *s);
void *validate_mb(const void *str);
int outch(int c);
void *pd_memmem(const void *buf, size_t buflen, const void *pattern,
                size_t len);
void restore_term(int const fd);
void setup_term(int const fd);
void strip_ansi_color(char *s, toggle_t * toggle);
int strprefix(char *str1, char *str2);

int tst_cb(void *elem);
int tst_cb_cli(void *elem);
void tst_cleanup(tst_node_t * p);
tst_node_t *tst_insert(tst_node_t * p, wchar_t * w, void *data);
void *tst_prefix_search(tst_node_t * root, wchar_t * w,
                        int (*callback) (void *));
void *tst_search(tst_node_t * root, wchar_t * w);
int tst_traverse(tst_node_t * p, int (*callback) (void *), int first_call);

int ini_load(const char *filename, win_t * win, term_t * term,
             limits_t * limits, int (*report) (win_t * win, term_t * term,
                                               limits_t * limits,
                                               const char *section,
                                               const char *name, char *value));
int get_ini_attr(char *str, txt_attr_t * v, int max_color);
int ini_cb(win_t * win, term_t * term, limits_t * limits, const char *section,
           const char *name, char *value);
char *make_ini_path(char *name, char *base);

void set_foreground_color(term_t * term, int color);
void set_background_color(term_t * term, int color);

int build_metadata(word_t * word_a, term_t * term, int count, win_t * win);
int disp_lines(word_t * word_a, win_t * win, toggle_t * toggle, int current,
               int count, int search_mode, char *search_buf, term_t * term,
               int last_line, char *tmp_max_word, langinfo_t * langinfo);
void get_message_lines(char *message, ll_t * message_lines_list,
                       int *message_max_width, int *message_max_len);
int disp_message(ll_t * message_lines_list, int width, int max_len,
                 term_t * term, win_t * win);
void disp_word(word_t * word_a, int pos, int search_mode, char *buffer,
               term_t * term, win_t * win, char *tmp_max_word);
int egetopt(int nargc, char **nargv, char *ostr);
int expand(char *src, char *dest, langinfo_t * langinfo);
int get_bytes(FILE * input, char *mb_buffer, ll_t * word_delims_list,
              toggle_t * toggle, langinfo_t * langinfo);
int get_scancode(unsigned char *s, int max);
char *get_word(FILE * input, ll_t * word_delims_list, ll_t * record_delims_list,
               char *mb_buffer, unsigned char *is_last, toggle_t * toggle,
               langinfo_t * langinfo, win_t * win, limits_t * limits);
void left_margin_putp(char *s, term_t * term, win_t * win);
int main(int argc, char *argv[]);
void right_margin_putp(char *s1, char *s2, langinfo_t * langinfo, term_t * term,
                       win_t * win, int line, int offset);
int search_next(tst_node_t * tst, word_t * word_a, char *search_buf,
                int after_only);
void sig_handler(int s);

void parse_cols_selector(char *str, char **filter, char *unparsed,
                         int max_cols, ll_t ** inc_list, ll_t ** exc_list);
void set_new_first_column(win_t * win, term_t * term, word_t * word_a);

int parse_sed_like_string(sed_t * sed);
int replace(char *orig, sed_t * sed, char *buf, size_t bufsiz);

int decode_txt_attr_toggles(char *s, txt_attr_t * attr);
int parse_txt_attr(char *str, txt_attr_t * attr, short max_color);
void apply_txt_attr(term_t * term, txt_attr_t attr);
