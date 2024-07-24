#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

//For the bonus part
//typedef struct s_list
//{
//	void			*content;
//	struct s_list	*next;
//}	t_list;

//libft bonus
typedef struct s_liblst
{
	void				*content;
	struct s_liblst		*next;
}	t_liblst;

t_liblst		*ft_lstnew(void *content);
void			ft_lstadd_front(t_liblst **lst, t_liblst *new);
int				ft_lstsize(t_liblst *lst);
t_liblst		*ft_lstlast(t_liblst *lst);
void			ft_liblstadd_back(t_liblst **lst, t_liblst *new);
void			ft_lstdelone(t_liblst *lst, void (*del)(void *));
void			ft_lstclear(t_liblst **lst, void (*del)(void *));
void			ft_lstiter(t_liblst *lst, void (*f)(void *));
t_liblst		*ft_lstmap(t_liblst *lst, void *(*f)(void *),
					void (*del)(void *));

// libft
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
// liste chainée

// ft_printf
int				ft_printf(const char *str, ...);
void			ft_putnbr_unsigned(unsigned int n, int fd);
int				ft_putchar(char c);
int				ft_putnbr_unsigned_size(int nbr);
int				ft_putnbr_size(int nbr);
int				ft_putstr(char *str);
int				ft_putnbr_base_size(unsigned long nbr, char *base);
int				ft_check_pourcent(char type, va_list args);

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char			*get_next_line(int fd);
size_t			ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);
char			*ft_strjoin_dup(char *s1, const char *s2);
char			*delete_buf_line(char *buf);
char			*fill_buffer(char *buf, int fd);

// autre ajout perso
void			ft_free_table(char **table);
long long int	ft_atol(const char *str);
void			ft_tabcpy(int *src, int*cpy, int size_max);
void			ft_free_verif(void **ptr);
size_t			ft_strlen_double(char **str);
#endif
