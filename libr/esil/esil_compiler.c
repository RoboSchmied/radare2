#include <r_esil.h>

typedef struct {
	REsil *esil;
} REsilCompiler;

typedef struct {
	char *error;
} REsilResult;

R_API REsilCompiler *r_esil_compiler_new(void) {
	REsilCompiler *ec = R_NEW0 (REsilCompiler);

	return ec;
}

R_API void r_esil_compiler_use(REsilCompiler *ec, REsil *esil) {
	R_RETURN_IF_FAIL (ec);
	ec->esil = esil;
}

typedef struct {
	const char *tok;
	const char *cur;
	bool available;
} ParseState;

static char peek(ParseState *ps) {
	char ch = ps->cur[0];
	if (ch == 0) {
		ps->available = false;
	}
	ps->cur++;
	return ch;
}

static void sep(ParseState *ps) {
	int toklen = ps->cur - ps->tok;
	printf ("TOKEN = %.s\n", toklen, ps->tok);
}

R_API void r_esil_compiler_parse(REsilCompiler *ec, const char *expr) {
	ParseState ps = {expr, expr, true};
	R_RETURN_IF_FAIL (ec);
	// parse a space separated list of tokens
	for (;ps.available;) {
		switch (peek (&ps)) {
		case 0:
			break;
		case '\n':
		case '\t':
		case ' ':
			sep (&ps);
			break;
		}
	}
}

R_API char *r_esil_compiler_tostring(REsilCompiler *ec) {
	// render the expression
}

R_API void r_esil_compiler_free(REsilCompiler *ec) {
	free (ec);
}

int main() {
	const char code[] = "( my macro ) : ADD + ; 1 1 ADD rax :=";
	REsilCompiler *ec = r_esil_compiler_new ();
	r_esil_compiler_parse (ec, code);
	r_esil_compiler_free (ec);
}
