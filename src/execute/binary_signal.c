/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   binary_signal.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 17:33:06 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 04:40:03 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		binary_signal(int status, int pid, char *bin)
{
	char	*tmp;

	if ((status >= 6 && status <= 8) || (status >= 11 && status <= 16))
	{
		ft_putstr_fd("[1]\t", 2);
		tmp = ft_itoa(pid);
		ft_putstr_fd(tmp, 2);
		write(2, " ", 1);
		ft_strdel(&tmp);
	}
	if (status == 6)
		ft_putstr_fd("ABORT", 2);
	if (status == 7)
		ft_putstr_fd("BUS ERROR", 2);
	if (status == 8)
		ft_putstr_fd("FLOATING-POINT EXEPTION", 2);
	if (status == 11)
		ft_putstr_fd("SEGMENTATION FAULT", 2);
	if (status == 13)
		ft_putstr_fd("BROKEN PIPE", 2);
	if (status == 16)
		ft_putstr_fd("STACK FAULT", 2);
	if ((status >= 6 && status <= 8) || (status >= 11 && status <= 16))
	{
		write(2, "\t", 1);
		ft_putendl_fd(bin, 2);
	}
	return (0);
}
/*
 *	1SIGHUPinstruction (HANG UP) - Fin de session
 *	2SIGINTinterruption
 *	3SIGQUITinstruction (QUIT)
 *	4SIGILLinstruction illégale
 *	5SIGTRAPtrace trap
 *	6SIGABRT (ANSI)Instruction (ABORT)
 *	6SIGIOT (BSD)IOT Trap
 *	7SIGBUSbus error
 *	8SIGFPEfloating-point exception - Exception arithmétique
 *	9SIGKILLinstruction (KILL) - termine le processus immédiatement
 *	10SIGUSR1signal utilisateur 1
 *	11SIGSEGVviolation de mémoire
 *	12SIGUSR2signal utilisateur 2
 *	13SIGPIPEbroken PIPE - Erreur PIPE sans lecteur
 *	14SIGALRMalarme horloge
 *	15SIGTERMsignal de terminaison
 *	16SIGSTKFLTstack Fault
 *	17SIGCHLD ou SIGCLDmodification du statut d'un processus fils
 *	18SIGCONTdemande de reprise du processus
 *	19SIGSTOPdemande de suspension imbloquable
 *	20SIGTSTPdemande de suspension depuis le clavier
 *	21SIGTTINlecture terminal en arrière-plan
 *	22SIGTTOUécriture terminal en arrière-plan
 *	23SIGURGévènement urgent sur socket
 *	24SIGXCPUtemps maximum CPU écoulé
 *	25SIGXFSZtaille maximale de fichier atteinte
 *	26SIGVTALRMalarme horloge virtuelle
 *	27SIGPROFprofiling alarm clock
 *	28SIGWINCHchangement de taille de fenêtre
 *	29SIGPOLL (System V)occurence d'un évènement attendu
 *	29SIGIO (BSD)I/O possible actuellement
 *	30SIGPWRpower failure restart
 *	31SIGSYSerreur d'appel système
 */
