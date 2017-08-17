#include "ls.h"
void	ft_rotate(t_ls **stock, char *name, const char *foldername)
{
	t_ls	*y;
	t_ls	*x;
	t_ls	*z;

	z = *stock;
	if ((y = (*stock)->left) && !(*stock)->left->color && (x = (*stock)->left->left) && !(*stock)->left->left->color )
	{
		z->left = y->right;
		y->right = z;
		y->left = x;
		*stock = y;
	}
	else if ((x = (*stock)->left) && !(*stock)->left->color &&  (y = (*stock)->left->right) && !(*stock)->left->right->color )
	{
		z->left = y->right;
		x->right = y->left;
		y->right = z;
		y->left = x;
		*stock = y;
		return;
	}
	else if ((y = (*stock)->right) && !(*stock)->right->color && (z = (*stock)->right->right) && !(*stock)->right->right->color )
	{
		x = *stock;
		x->right = y->left;
		y->right = z;
		y->left = x;
		*stock = y;
		return;
	}
	else if ((z = (*stock)->right) && !(*stock)->right->color && (y = (*stock)->right->left) && !(*stock)->right->left->color )
	{
		x = *stock;
		x->right = y->left;
		z->left = y->right;
		y->right = z;
		y->left = x;
		*stock = y;
		return;
	}
	else if (ft_strcmp((*stock)->name, name) > 0)
		ft_rotate(&(*stock)->left, name, foldername);
	else if (ft_strcmp((*stock)->name, name) > 0)
		ft_rotate(&(*stock)->right, name, foldername);
}
