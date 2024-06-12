

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "minilibx-linux/mlx.h"
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700
#define RED 0xFF0066
#define ORANGE 0xFF9933
#define YELLOW 0xFFFF00
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define PURPLE 0xFF00FF
#define MAGENTA 0xFF66FF
#define CIAN 0x00FFFF
#define TURKEY 0x00FFCC
#define LIME 0x7FFF00
#define FUCSIA 0xF600CA
#define ERROR_MESSAGE "Error de Parametros"

typedef struct s_complex
{
	double real;
	double imaginary;
}     t_complex;


typedef struct s_img
{
	void    *img_ptr;
	char    *img_pixels_ptr;
	int     bpp;
	int     endian;
	int     line_len;
}   t_img;

typedef struct s_windows
{
	void    *mlx_ptr;
	void    *win_ptr;
	double  x;
	double  y;
	double real;
	double imaginary;
	t_img   img;
	double escape;
	int iterations;
	double move_x;
	double move_y;
	double zoom;
	char *type_fract;
}   t_windows;

// void put_color_to_pixel(t_windows *fractal, int x, int y, unsigned int color) {
//     if (x >= 0 && x < 799 && y >= 0 && y <  799) {
//         // Check if pixel is within the image bounds
//         unsigned int *pixel_ptr = (unsigned int *)fractal->img->img_pixels_ptr + (y * 799 + x);
//         *pixel_ptr = color; // Set the pixel color
//     }
// }


void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
	write(1, "\n",1);
}

void ft_menu()
{
	ft_putstr("Debe introducir alguna de las siguientes fractales disponibles");
	ft_putstr("Mandelbrot");
	ft_putstr("Julia  <real> <imaginaria>");
	ft_putstr("Caos");
	//ft_putstr("");
	//ft_putstr("");
}
void put_color_to_pixel(t_img *img, int x, int y, int color)
{
	// Access pixel data directly using member variables from the img structure
	int *pixel_ptr = (int *)(img->img_pixels_ptr + (y * img->line_len / 4) + (x * (img->bpp / 8))); // Consider endianness if needed
	*pixel_ptr = color;
}



t_complex num_complex(double x, double y, int iteration)
{
	t_complex complex;

	complex.real = ((x * x) - (y * y));// + x;
	complex.imaginary = (2 * x * y);// + y;
	return (complex);
}

int	ft_iterative_power(int nb, int power)
{
	int	result;

	result = 1;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 0)
	{
		result *= nb;
		power--;
	}
	return (result);
}


char *ft_inspace(char *str)
{
	int		i;
	int		sign;
	
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	return (str);
}

double    ft_atof(const char *str)
{
    int		sign;
    double	result;
    double	decimal;
    int		i;
    int		j;
    j = 0;

    i = 0;
    sign = 1;
    result = 0;
    decimal = 0;
    j = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if (str[i] == 43 || str[i] == 45)
    {
        if (str[i] == 45)
            sign *= -1;
        i++;
    }
    while (str[i] >= 48 && str[i] <= 57 && str[i] != '.')
    {
        result = result * 10 + (str[i] - 48);
        i++;
    }
    i++;
    while(str[i] >= 48 && str[i] <= 57)
    {
        decimal = decimal * 10 + (str[i] - 48);
        i++;
        j++;
    }
    result += decimal / ft_iterative_power(10,j);
    return (result * sign);
}

double	ft_atoi(const char *str)
{
	int	sign;
	double	result;
	int	i;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

double	ft_scale_down(double x, double a, double b, double min, double max) 
{
	return (b - a) * (x - min) / (max - min) + a;
}

t_complex	ft_calculate_number_complex (double zx,double zy, double cx,double cy)
{
	  t_complex   complex;

		complex.real = ((zx * zx) - (zy * zy));// + x;
		complex.imaginary = (2 * zx * zy);
		complex.real += cx;
		complex.imaginary += cy;
		return (complex);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0') && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);

}



// ft_scalinfg fir eal y imaginary
// iteration y su complex
// scaling 
//
static void ft_color(int x, int y, t_img *img, int color)
{
	int offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->img_pixels_ptr + offset) = color;
}

int	close_handler( t_windows *fract)
{
	mlx_destroy_window(fract->mlx_ptr,
						fract->win_ptr);
	mlx_destroy_display(fract->mlx_ptr);
	free(fract->mlx_ptr);
	exit(EXIT_SUCCESS);
}
static void ft_data_init_fract (t_windows *fract)
{
	fract->iterations = 100;
	fract->escape = 4;
	fract->move_x = 0.0;
	fract->move_y = 0.0;
	fract->zoom = 1.0;
}



static void ft_draw2(int x, int y, t_windows *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	// pixel coordinate x && y scaled to fit mandel needs 
	//
	c.real = -0.8;
	c.imaginary = 0.156;
	z.real = (ft_scale_down(x, -2, +2, 0, WINDOW_WIDTH) * fractal->zoom);
	z.imaginary = (ft_scale_down(y, +2, -2, 0, WINDOW_HEIGHT) * fractal->zoom);
	//	to check if the point escaped?
	while (i < 42)
	{
//		z = sum_complex(square_complex(z), c);
		if ((z.real * z.real) + (z.imaginary * z.imaginary) > 4)
		{
			color = ft_scale_down(i, LIME, GREEN, 0, 42);
			ft_color(x, y, &fractal->img, color);
			return ;
		}
		++i;	
	}
	// We are in MANDELBROT given the iterations made
	ft_color(x, y, &fractal->img, FUCSIA);
}

// JULIA



// static void ft_caos (int x, int y, t_windows *fract)



// Function to calculate the Lorenz system (replace ft_calculate_number_complex)
t_complex ft_lorenz_calculation(t_complex z, double sigma, double rho, double beta)
{
	t_complex new_z;
	new_z.real = sigma * (z.real - z.imaginary);
	new_z.imaginary = rho * z.real - z.real * z.imaginary - beta * z.imaginary;
	return new_z;
}

static void ft_lorenz(int x, int y, t_windows *fract) {
    // Adjust these scaling factors for desired position and size
    double scale_x = WINDOW_WIDTH / 50.0;
    double scale_y = WINDOW_HEIGHT / 50.0;
    double offset_x = WINDOW_WIDTH / 2.0;
    double offset_y = WINDOW_HEIGHT / 2.0;

    double a = 10.0, b = 28.0, c = 8.0 / 3.0;
    double dt = 0.001; // Smaller timestep for smoother visualization

    // Initial conditions (can be adjusted for different attractor shapes)
    double x0 = 0.01, y0 = 0.0, z0 = 0.0;
    double  z;

    for (int i = 0; i < 100; i++) {
        // Calculate Lorenz system derivatives
        double dx = a * (y0 - x0) * dt;
        double dy = (x0 * (b - z0) - y0) * dt;
        double dz = (x0 * y0 - c * z0) * dt;

        // Update state variables
        x = x0 + dx;
        y = y0 + dy;
        z = z0 + dz;

        // Update initial conditions for next iteration
        x0 = x;
        y0 = y;
        z0 = z;

        // Scale and translate coordinates for plotting
        int scaled_x = (int) (scale_x * x + offset_x);
        int scaled_y = (int) (scale_y * y + offset_y);

        // Check if within window bounds (avoid out-of-bounds writes)
        if (scaled_x >= 0 && scaled_x < WINDOW_WIDTH && scaled_y >= 0 && scaled_y < WINDOW_HEIGHT) {
            // Color based on iteration number (or a more complex coloring scheme)
            int color = ft_scale_down(i, BLUE, RED, 0, 100);
            ft_color(scaled_x, scaled_y, &fract->img, color);
        }
    }
}

void ft_burning_ship(int x, int y, t_windows *fract) {
    t_complex   z;
    t_complex   c;
    int         i;
    int         color;

    i = 0;
    c.real = -0.5;
    c.imaginary =  0.05;
    z.real = (ft_scale_down(x, -2, +2, 0, WINDOW_WIDTH) * (1 /fract->zoom)) + fract->move_x;
    z.imaginary = (ft_scale_down(y, +2, -2, 0, WINDOW_HEIGHT) * (1 / fract->zoom)) + fract->move_y;

    while (i < fract->iterations) {
        // Absolute value for both real and imaginary parts in Burning Ship
       z = ft_calculate_number_complex( fabs(z.real), fabs(z.imaginary), fabs(c.real) ,fabs(c.imaginary));
      
        if ((fabs(z.real) * fabs(z.real)) + (fabs(z.imaginary) * fabs(z.imaginary)) >= 4) {
            color = ft_scale_down(i, LIME, GREEN, 0, fract->iterations);
            ft_color(x, y, &fract->img, color);
            return;
        }

        ++i;
    }

    ft_color(x, y, &fract->img, 0xFFFFFF);  // Black for non-diverging points
}

void ft_julia(int x, int y, t_windows *fract)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	c.real = fract->real;
	c.imaginary =  fract->imaginary;
	z.real = (ft_scale_down(x, -2, +2, 0, WINDOW_WIDTH) * (1 /fract->zoom)) + fract->move_x;
	z.imaginary = (ft_scale_down(y, +2, -2, 0, WINDOW_HEIGHT) * (1 / fract->zoom)) + fract->move_y;
		while (i < fract->iterations)
		{
			z = ft_calculate_number_complex( z.real, z.imaginary, c.real ,c.imaginary);
			if ((z.real * z.real) + (z.imaginary * z.imaginary) >= 4)
			{
				color = ft_scale_down(i, LIME, GREEN, 0, fract->iterations);
				ft_color(x, y, &fract->img, color);
				return ;
			}
		++i;
		 }
	ft_color(x, y, &fract->img, 0xFFFFFF);
}

void ft_mandelbrot(int x, int y, t_windows *fract)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.real = 0.0;
	z.imaginary = 0.0;
	c.real = (ft_scale_down(x, -2, +2, 0, WINDOW_WIDTH) * (1 /fract->zoom)) + fract->move_x;
	c.imaginary = (ft_scale_down(y, +2, -2, 0, WINDOW_HEIGHT) * (1 / fract->zoom)) + fract->move_y;
		while (i < 10)
		{
			z = ft_calculate_number_complex( z.real, z.imaginary, c.real ,c.imaginary);
			if ((z.real * z.real) + (z.imaginary * z.imaginary) > 4)
			{
				color =  ft_scale_down (i, BLUE, GREEN,0, 10);
				ft_color(x,y,&fract->img, color);
				return ;
			}
		 	i++;
            printf("%f %f %d \n",z.real,z.imaginary, i);  exit(1);
		 }
       
	ft_color(x, y, &fract->img, FUCSIA);
}

void render(struct s_windows *fract)
{
	int x;
	int y = 0;

	while (y++ < WINDOW_HEIGHT - 1)
	{
		x = 0;
		while (x++ < WINDOW_WIDTH - 1)
		{
			if(fract->type_fract == "Julia")
				ft_julia(x,y,fract);
			else if (fract->type_fract == "Mandelbrot")
				ft_mandelbrot(x,y,fract);
		   else if (fract->type_fract == "Caos")
				ft_burning_ship(x,y,fract);
			
		}
	}
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->img.img_ptr, 0, 0);
	// comenzamos en la position 0
}
void ft_error()
{
	write(1,"ERROR",5);
}
// Cerrar ventana
int	close_handle(void)
{
	exit(2);
	return (2);
}
int handle_keypress(int keysym, struct s_windows *fract)
{
	if (keysym == XK_Escape)
	   close_handler(fract);
	 // 65361
 if ( keysym == XK_Left)
	fract->move_x += 0.05 * (1 / fract->zoom);
// 65362
 if ( keysym == XK_Up)
	fract->move_y -= 0.05 * (1 / fract->zoom);
// 65363
 if ( keysym == XK_Right)
	fract->move_x -= 0.05 * (1 / fract->zoom);
// 65364
if ( keysym == XK_Down)
	fract->move_y += 0.05 * (1 / fract->zoom);
 if (keysym == 65451)
	fract->iterations += 1;

if (keysym == 65453)
	fract->iterations -= 1;
	 printf("Keypress: %i\n", keysym);
	render(fract);
	 return 0;
}

double	map(double num, double n_min, double n_max, double o_max)
{
	return ((n_max - n_min) * num / o_max + n_min);
}

int mouse_handle(int button,int x,int y, struct s_windows *fract)
{
	if (button == 4)
	{
		fract->zoom *= 1.7;
	}
	if(button == 5)
	{
		fract->zoom *= 0.3;
	}
	fract->move_x += ft_scale_down(x, -2, 2,fract->move_x, WINDOW_WIDTH) * (1 / fract->zoom);
	fract->move_y += ft_scale_down(y, 2, -2,  fract->move_y,WINDOW_HEIGHT) * (1 / fract->zoom);
	printf("zoom %f.\n",fract->zoom);
	printf("Mouse in Win1, button %d at %dx%d.\n",button,x,y);
	render(fract);
	return (0);
}
void ft_event(struct s_windows *fract)
{
	mlx_hook(fract->win_ptr, KeyPress,KeyPressMask, handle_keypress, fract);
	mlx_hook(fract->win_ptr, ButtonPress, ButtonPressMask, mouse_handle, fract);
   // mouse event
	// mlx_mouse_hook(fract->win_ptr, mouse_hook, fract);
	// cerrar ventana 
	mlx_hook(fract->win_ptr, DestroyNotify, StructureNotifyMask, close_handle, fract);
}


void fract_up( struct s_windows *fract)
{
	void *mlx = mlx_init();
	if (NULL == mlx)
		ft_error();
	void *win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Fractal");
  	if (NULL == mlx)
	{
		mlx_destroy_display(mlx); // Cleanup MLX connection
		free(mlx);
		ft_error();
	}
	fract->mlx_ptr = mlx; // Initialize data.mlx_ptr and data.win_ptr
	fract->win_ptr = win;
	fract->img.img_ptr = mlx_new_image(fract->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	 if (fract->img.img_ptr == NULL)
	{
		mlx_destroy_window(mlx,win);
		mlx_destroy_display(mlx); // Cleanup MLX connection
		free(mlx);
		ft_error();
	}
	fract->img.img_pixels_ptr = mlx_get_data_addr(fract->img.img_ptr, &fract->img.bpp, &fract->img.line_len, &fract->img.endian);
	ft_data_init_fract(fract);
	ft_event(fract);
}


void ft_check_parameters_fractal(int argc, char **argv)
{
	 t_windows fract;

	 if (ft_strcmp(argv[1],"Julia") == 0 && argc == 4)
	 {
		fract.type_fract = "Julia";
		fract.real = ft_atof(argv[2]);
		fract.imaginary = ft_atof(argv[3]);
		fract_up(&fract);
		render(&fract);
		mlx_loop(fract.mlx_ptr);
	 }
	if (ft_strcmp(argv[1],"Mandelbrot") == 0)
	{
		fract.type_fract = "Mandelbrot";
		fract_up(&fract);
		render(&fract);
		mlx_loop(fract.mlx_ptr);
	}
	if (ft_strcmp(argv[1],"Caos") == 0)
	{
		fract.type_fract = "Caos";
		fract_up(&fract);
		render(&fract);
		mlx_loop(fract.mlx_ptr);
	}
	else
	{
		ft_menu();
		exit(EXIT_FAILURE);
	}
}


int main(int argc, char **argv)
{
	//t_complex complex;
	ft_check_parameters_fractal(argc, argv);
	//write(1,"entrol",6);
	return (0);
}



