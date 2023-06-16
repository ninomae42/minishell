#include "parser.h"

char	*node_kind_to_str(t_node_kind kind)
{
	if (kind == ND_WORD)
		return ("ND_WORD");
	if (kind == ND_REDIRECT_IN)
		return ("ND_REDIRECT_IN");
	if (kind == ND_REDIRECT_IN_HDOC)
		return ("ND_REDIRECT_IN_HDOC");
	if (kind == ND_REDIRECT_OUT)
		return ("ND_REDIRECT_OUT");
	if (kind == ND_REDIRECT_OUT_APPEND)
		return ("ND_REDIRECT_OUT_APPEND");
	if (kind == ND_SIMPLE_COMMAND)
		return ("ND_SIMPLE_COMMAND");
	if (kind == ND_PIPELINE)
		return ("ND_PIPELINE");
	return ("UNKNOWN");
}
