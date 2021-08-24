#include "../includes/minishell.h"


int	change_dir_to_arg(char *dir)
{
	char	*tmp;

	// getcwd로 현재 pwd 받는다.(동적할당됨)
	// 동적할당 NULL 가드
	tmp = getcwd(NULL, 0);
	if (tmp != NULL)
	{
		print_error(MALLOC_ERROR, "cd");
		return (1);
	}

	// OLDPWD 변수를 tmp1의 값으로 교체
	// OLDPWD가 이미 unset되었으면 음수 반환받음.
	// 어쨌거나 cd커맨드에는 상관 없으므로 에러 처리 하지 않기로
	set_new_value_to_existing_key("OLDPWD", tmp);


	// chdir()해서 cdw 바꿔준다.
	// 에러 가드(에러 출력 및 리턴 1)
	if (chdir(dir) < 0)
	{
		print_error(ERRNO_SET, "cd");
		return (1);
	}

	// getcwd(NULL, 0);으로 현재 경로 스트링 동적 할당받기
	// 동적할당 에러 가드(에러 출력 및 리턴 1)
	tmp = getcwd(NULL, 0);
	if (tmp != NULL)
	{
		print_error(MALLOC_ERROR, "cd");
		return (1);
	}


	// PWD 변수를 위에서 할당 받은 현재 경로 스트링으로 교체
	// PWD가 이미 unset되었으면 음수 반환받음.
	// 어쨌거나 cd커맨드에는 상관 없으므로 에러 처리 하지 않기로
	set_new_value_to_existing_key("PWD", tmp);
	return (0);
}

int	builtin_cd(int i)
{
	char	*tmp;
	int		ret;

	if (g_info.cmds[i][1] == NULL)
	{
		tmp = find_env_var("HOME");
		if (tmp == NULL)
		{
			print_error(MALLOC_ERROR, "cd");
			return (1);
		}
		return (change_dir_to_arg(tmp));
	}
	else if (g_info.cmds[i][2] == NULL)
	{
		return (change_dir_to_arg(g_info.cmds[i][1]));
	}
	else
	{
		ft_putstr_fd("minisehll: cd: too many arguments\n", 2);
		return (1)
	}
}
