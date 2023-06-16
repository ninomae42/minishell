#include "tokenizer.h"

char	*token_kind_to_str(t_token_kind kind)
{
	if (kind == TK_WORD)
		return ("TK_WORD");
	if (kind == TK_REDIRECT_IN)
		return ("TK_REDIRECT_IN");
	if (kind == TK_REDIRECT_IN_HDOC)
		return ("TK_REDIRECT_IN_HDOC");
	if (kind == TK_REDIRECT_OUT)
		return ("TK_REDIRECT_OUT");
	if (kind == TK_REDIRECT_OUT_APPEND)
		return ("TK_REDIRECT_OUT_APPEND");
	if (kind == TK_PIPELINE)
		return ("TK_PIPELINE");
	if (kind == TK_EOF)
		return ("TK_EOF");
	return ("UNKNOWN");
}
