# Fract-ol MinilibX
## Prototype n functions:
int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
void	*mlx_new_window(void *mlx_ptr,int size_x,int size_y,char *title);

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

x, y. it is considered that the top left corner of the screen is the origin (x = 0, y = 0).

Let's consider a common screen resolution, that is 1920x1080.
x = colonnes, y = ligne (nbr pixel)
In this case, that means that there's 1080 rows of pixels on the screen, and that
each row has 1920 pixels. The y axis is used to represent the row number, while
the x axis is used to represent the column number.

## Events
![[Pasted image 20221226162107.png]]
Clicking anywhere in the window with the mouse is an event. Pressing a key is another. Events are basically everything the user can do to interact with the program.

To make the program interactive, events are a must have. Before the `mlx_loop` function is called, the minilibx allows us to **register events** that are able to be triggered after the loop has started. The minilibx calls these functions **hooks**.

`int handle_keypress(int keysm, t_data *data)
`int render(t_data *data)

Functions hook pour gerer les events avant que mlx_loop soit appele
- `int	mlx_mouse_hook (void *win_ptr, int (*funct_ptr)(), void *param);`
- `int	mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param);`
- `int	mlx_expose_hook (void *win_ptr, int (*funct_ptr)(), void *param);`
- `int	mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);`
- `int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param)

Autres fonctions:
- mlx_loop (apres les fonctions hook)
- int	handle_no_event(void *data)

Utilisation de structures pour pouvoir passer plusieurs variables dans une fonction a 1 para.
- t_data object

### mlx_key_hook:
`int	mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param);`

Executee a chaque fois qu'une cle(touche) est lancee dans handle_input.
Check quelle cle a ete lancee (et faire la suite). We also pass the address of data which
is the t_data object that contains all the stuff that we need to access inside handle_input.

### handle_input:
`int	handle_input(int keysym, t_data *data)`

controle si le symbole de la cle lancee correspond a the escape key. (include X11/keysym.h)
key code != key symbol (keysym). Key code for the "A" on AZERTY will be the same than
key code for  "Q" on QWERTY.
If the key I expect to be pressed is "A", I want it to be "A" whatever the keyboard layout of the user is. I want to get it by the symbol. This conversion is done by the minilibx internally. What we're getting in handle_input is the correct key symbol.

If the symbol check evaluates to true, then that means the escape key has been released, so we destroy the window. Because the window gets destroyed, the mlx_loop ends as there's no window left.

### mlx_expose_hook:
`int	mlx_expose_hook (void *win_ptr, int (*funct_ptr)(), void *param);`

Expose events are triggered when the content of a window gets lost (for example, when the minilibx's window is covered partially or entirely by another) and needs to be re-drawn.

### mlx_loop_hook:
`int	mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);`

When no event processed.  Useful to drawn thing continuously on the screen = render/draw function.


### mlx_hook:
`int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param)

key pressed != key released (different event). mlx_key_hook et mlx_key_hook gere seulement un event en meme temps. (KeyRelease pour keyboard event).  Try to run the program and press the escape key **without releasing it**. You'll notice that nothing happens unless you release the key. That's because we registered to a `KeyRelease` event. However, we need an alternative for other events that the X Window System handles. That's exactly what the `mlx_hook` is used for.
Fonction plus generique, remplace mlx_key_hook:
`mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data); /* ADDED */
`mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data); /* CHANGED */

### Code exemple:
```c
#include <X11/keysym.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int	handle_no_event(void *data)
{
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup hooks */ 
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_key_hook(data.win_ptr, &handle_input, &data);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
```

```c
#include <X11/X.h>

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);

	printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
	printf("Keyrelease: %d\n", keysym);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup hooks */ 
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data); /* ADDED */
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data); /* CHANGED */

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
```

## Drawing Pixel
### mlx_pixel_put
```int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);```
Pour dessiner pixel. 
True Color Standard: RGB
Two ways:
- By setting the bits
```c
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}
```
- hexadecimal notation
Hexadecimal is widely used when using encoded values because it allows us to clearly distiguish the bytes that form an integer. To do so, we need to think about an hexadecimal number as groups of two digits. One group of two digits represents an entire byte.

`0x00FF00FF`:  red is FF (255), green is 0 and blue is FF (255).

This solution is interesting **only if we already know what color we want to use at compile time**. If the color is somehow provided by the user or from any external source, we will need to use the `encode_rgb` function.

### First pixel
```c
#include <stdlib.h>
#include <stdio.h>

#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 300

#define MLX_ERROR 1

#define RED_PIXEL 0xFF0000

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	render(t_data *data)
{
	/* if window has been destroyed, we don't want to put the pixel ! */
	if (data->win_ptr != NULL)
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, 
			WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, RED_PIXEL);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
								"my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup hooks */ 
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
```

#### Render function
Here, we're making use of the `render` function, the address of which is passed to the `mlx_loop_hook` function. In the previous post, we called this function `handle_no_event`, because it is triggered continuously while the loop is running. Because the `render` function's code needs to be run at each frame, we can use it to render all the things we want to display on the screen!

#### A small check to be safe
Please notice the `if` statement added before the `mlx_pixel_put` function. This statement is here to ensure the window still exists, to avoid puting a pixel on a window that is no longer available. Because of how `mlx_loop` is implemented, this is what would have happened if we didn't add this check. Moreover, we needed to ensure that our `win_ptr` was set to `NULL` after the call to `mlx_destroy_window` to make this check actually work.

### Drawing a rectangle
```c
#define GREEN_PIXEL 0xFF00

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

/* The x and y coordinates of the rect corresponds to its upper left corner. */

int render_rect(t_data *data, t_rect rect)
{
	int	i;
	int j;

	if (data->win_ptr == NULL)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
		++i;
	}
	return (0);
}
```
```int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);```
We have to modify the render function to draw a rectangle:
```c
int	render(t_data *data)
{
	render_rect(data, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100,
			100, 100, GREEN_PIXEL});
	render_rect(data, (t_rect){0, 0, 100, 100, RED_PIXEL});

	return (0);
}
```

In case you're wondering, `(t_rect){}` is what is called a _compound literal_. Since C99, this is a way to initialize structures without having to manually assign each member. I'm directly passing a structure by value here.

These `render_rect` function calls will display two rectangles: one in the upper left corner of the window (red), and the other in the bottom right corner (green).
![[Pasted image 20221226135906.

### The mlx_pixel_put problem
- render_background function:
```c
void	render_background(t_data *data, int color)
{
	int	i;
	int	j;

	if (data->win_ptr == NULL)
		return ;
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, color);
		++i;
	}
}
```
- Add the render_background function to the render function:
```c
int	render(t_data *data)
{
	render_background(data, WHITE_PIXEL);
	render_rect(data, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	render_rect(data, (t_rect){0, 0, 100, 100, RED_PIXEL});

	return (0);
}
```
- Resultat -> ca clignote salement.
The `mlx_pixel_put` function basically draws the pixel on the window directly, and the person who's looking at the window will see the change instantly. That's bad here because what we actually want to do is waiting for the whole background to be drawn, as well as the rectangles, and _then_ push that on the window. Because everything is done without any delay, this is giving us this dirty flickering effect.

### Use a image instead
Image = collection of pixels.
Minilibx uses Xshm extension (allows programs to share images with X server through shared memory, (/dev/shm)). 
With images (in shared memory), pixels are changed directly, using a pointer. Faster.

#### Preparation
```c
void	*mlx_new_image(void *mlx_ptr,int width,int height);
```

- Creer un type pour l'image:
```c
typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;
```
The `mlx_img` member refers to the address `mlx_new_image` returns.

#### Stocker  l'image dans la structure t_data:
```c
typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;
```

#### Create a new image
```c
data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
```

##### Use mlx_get_data_addr
```c
char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
```
`mlx_get_data_addr` function returns the actual address of the image as a simple array of pixels.
We're getting a pointer on `char`, which usually means we're going to naviguate in the array one byte at a time (not one pixel at a time, a pixel usually takes more than one byte as we've seen before).
- Provide an adress image in the shares memory (to change pixel directly). 
- Provide bpp (bits per pixel), line_len, endian (infos necessaires pour calculer).

We need to pass it the img we've got from `mlx_new_image`. For the three last arguments, we simply need to pass the address of an `int` variable. The function will set these integers to the correct value. You can see that as a way to "return" multiple values.

#### Access to a particular image's pixel
We need to retrieve a pixel at some x and y coordinates, but we don't have a two dimensional array here: we're dealing with a one dimensional array. Also remember that we're dealing with bytes here, but one pixel takes more than one byte because we're using the true colors standard. This amount is given by the `bpp` (in bits) value we've got from `mlx_get_data_addr`.

##### Find the pixel's first byte's address
Exemple: pixel at (5,10)
Window dimensione: 600 pixels x 300 pixels

What we want is the **5th** pixel of the **10th row**.

- Find the row (y): The previous `mlx_get_data_addr` call provided us the `line_len` value, which is basically the **amount of bytes taken by one row of our image**. It is equivalent to `image_width * (bpp / 8)`.
- An `int` is four bytes, so it is `600 * 4 = 2400`. Therefore we can say that the first row begins at the index `0`, the second one at the index `2400`, the third one at the index `4800`, and so on. Thus we can find the correct row index by doing `2400 * 10`.
- To find the correct column, we will need to move in the row by the given number of pixels. In our case, we want to move 5 pixels "right". To do that, we need to multiply `5` by the number of bytes a pixel actually takes (here `4`). Thus we will do `5 * 4 = 20`.

If we summarize, we can find the correct index with the following computation: `index = 2400 * 10 + 5 * 4`.

That's it! We just need to generalize the formula using the values `mlx_get_data_addr` provided us. The following formula is the one we'll use:

```plain
index = line_len * y + x * (bpp / 8)
```
(bytes = 4 ou 8 bits (depend), bpp = 32, 128 bytes par pixel (4 x  32))
bit = 0-1.

-----------------------------------
##### Endianess:
If my computer reads **bytes** from left to right, and your computer reads from right to left, we're going to have issues when we need to communicate.

Endianness means that the bytes in computer memory are read in a certain order.

**Endianness** is represented two ways **Big-endian** (**BE**) and **Little-endian** (**LE**).

-   **BE** stores the **big-end** first. When reading multiple bytes the first byte (or the lowest memory address) is the biggest - so it makes the most sense to people who read left to right.
-   **LE** stores the **little-end** first. When reading multiple bytes the first byte (or the lowest memory address) is the littlest -  so it makes most sense to people who read right to left.

-----------------------------------------
Now that we have the formula, let's implement the `img_pix_put` function that will put a pixel at (x, y) coordinates of the image. It will act as a replacement for the `mlx_pixel_put` function.

```c
void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
```

That should work, but we've a problem here. If our bytes per pixel value is not equal to the size of an `int` on our system, we're not doing well. In most scenarios, they will be equal, and the above implementation will just work, but that's not really the most portable thing in the world.

I've came with what is (in my opinion) a more accurate way of doing it, taking the endianness in account.

```c
		while (j < rect.x + rect.width)
```


### Let's draw on the screen
#### Drawing functions refactoring
What we need to do now is to change every drawing function to make it use the `t_img` object instead of the window directly.

Avant, avec win_ptr:
```c
int render_rect(t_data *data, t_rect rect)
{
	int	i;
	int j;

	if (data->win_ptr == NULL)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
		++i;
	}
	return (0);
}```

Let's refactor the `render_rect` function:
```c
int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}
```

`render_backgroud` avec win_ptr:
```c
void	render_background(t_data *data, int color)
{
	int	i;
	int	j;

	if (data->win_ptr == NULL)
		return ;
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, color);
		++i;
	}
}
```

As well as `render_background`:
```c
void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}
```

#### Changing the render function
The most important change we need to do is in the `render` function:

```c
int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, WHITE_PIXEL);
	render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100,
		100, 100, GREEN_PIXEL});
	render_rect(&data->img, (t_rect){0, 0, 500, 300, RED_PIXEL});

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}
```

Now we're performing all our drawing operations on our image instead of directly pushing the pixels on the screen.

We then need to push the updated image on the window, which is done using `mlx_put_image_to_window`. Coordinates of the image are (0, 0) because it is covering the whole window. The `mlx_put_image_to_window` will push the image as well as the changes done to it (if any) at each frame.


#### DIVERS
On utilise "->" pour les pointeurs, et "." pour les variables.

##### Accès via un pointeur[](https://zestedesavoir.com/tutoriels/755/le-langage-c-1/1043_aggregats-memoire-et-fichiers/4279_structures/#acc%C3%A8s-via-un-pointeur)

Deux choses à gérer : l’accès via le pointeur et l’accès à un membre (champ). Intuitivement, vous combineriez sans doute les opérateurs `*` et `.` comme ceci.

```c
*p.heures = 1;
```

L'opérateur `.` s’applique _prioritairement_ à l’opérateur `*`. Autrement dit, le code ci-dessus accède au champ `heures` et tente de lui appliquer l’opérateur d’indirection, ce qui est incorrect puisque le membre `heures` est un entier non signé.

Pour résoudre ce problème, nous devons utiliser des parenthèses afin que l’opérateur `.` soit appliqué _après_ le déréférencement, ce qui donne la syntaxe suivante.

```c
(*p).heures = 1;
```

Cette écriture étant un peu lourde, le C fourni un autre opérateur qui combine ces deux opérations : l’opérateur `->`.

```c
p->heures = 1;
```

Le code suivant initialise donc la structure `t` via le pointeur `p`.

```c
struct temps t;
struct temps *p = &t;

p->heures = 1;
p->minutes = 45;
p->secondes = 30.560;
```

-> si pointeur sur struct (t_data *data) data est un ptr, **
struct temp *p;*

. si on veut modifier champ si juste type et non ptr (t_data data)
struct temps t;