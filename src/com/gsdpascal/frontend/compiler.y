%{
package com.gsdpascal.frontend;
import java.io.*;
import com.gsdpascal.astree.*;
import com.gsdpascal.codegen.*;
import java.util.ArrayList;
%}

%token T_PROGRAM T_CONST T_TYPE T_VAR
%token T_FUNCTION T_PROCEDURE
%token <ival> T_INT
%token <dval> T_REAL
%token <sval> T_ID T_CHAR T_STRING
%token T_BEGIN T_END
%token T_TRUE T_FALSE T_MAXINT
%token T_READ T_WRITE T_WRITELN T_ABS T_CHR T_ODD T_ORD T_PRED T_SQR T_SQRT T_SUCC
%token T_IF T_THEN T_ELSE T_REPEAT T_UNTIL T_WHILE T_DO T_CASE T_TO T_DOWNTO T_FOR
%token T_EQUAL T_UNEQUAL T_GE T_GT T_LE T_LT T_ASSIGN T_PLUS T_MINUS T_MUL T_DIV T_OR T_AND T_NOT T_MOD
%token T_LB T_RB T_LP T_RP T_SEMI T_DOT T_DOTDOT T_COMMA T_COLON
%token T_INTEGER_TYPE T_BOOLEAN_TYPE T_CHAR_TYPE T_REAL_TYPE
%token T_ARRAY T_OF T_RECORD T_GOTO
%token ERROR

%type <node> program routine routine_head routine_part function_decl function_head parameters para_decl_list para_type_list
%type <node> procedure_decl procedure_head var_part var_decl_list var_decl const_part const_expr_list const_expr const_value
%type <node> type_part  type_decl_list type_definition type_decl record_type_decl field_decl_list field_decl array_type_decl
%type <node> simple_type_decl name_list ID routine_body compound_stmt stmt_list no_label_stmt assign_stmt goto_stmt if_stmt
%type <node> else_clause repeat_stmt case_stmt case_expr_list case_expr for_stmt proc_stmt args_list expr
%type <node> term factor
%type <node> while_stmt expression stmt
%%

program             :   T_PROGRAM T_ID T_SEMI routine T_DOT
                        {   $$ = $4;
                            $$.setAttribute($2);
                            savedTree = $$;
                        }
                    | 	T_PROGRAM T_ID T_SEMI routine
                        {   $$ = $4;
                            $$.setAttribute($2);
                            savedTree = $$;
                            errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of end dot");
                        }
                    | 	T_PROGRAM T_ID routine T_DOT
                        {   $$ = $3;
                            $$.setAttribute($2);
                            savedTree = $$;
                            errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of semicolon");
                        }
                    | 	T_PROGRAM T_ID routine
                    	{   $$ = $3;
                            $$.setAttribute($2);
                            savedTree = $$;
                            errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of semicolon and end dot");
                        }
                    ;
routine             :   routine_head routine_body
                        {
                            $$ =$1;
                            $$.setSibling($2);
                        };
routine_head        :   const_part type_part var_part routine_part
                        {
                            $$ = new TreeNode(DeclarationKind.ROUTINEHEAD,yyline);
                            $$.addChild($1);
                            $$.addChild($2);
                            $$.addChild($3);
                            $$.addChild($4);
                        };
routine_part        :
                        {   $$= null;}
                    |   routine_part function_decl
                        {   TreeNode t=$1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($2);
                                $$=$1;
                            }
                            else
                                $$=$2;
                        }
                    |   routine_part procedure_decl
                        {   TreeNode t=$1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($2);
                                $$=$1;
                            }
                            else
                                $$=$2;
                        }
                    |   function_decl   {$$=$1;}
                    |   procedure_decl  {$$=$1;}
                    ;
function_decl       :   function_head T_SEMI routine T_SEMI
                        {
                            $$=new TreeNode(DeclarationKind.FUNCTION,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                        }
                    |	function_head T_SEMI routine
                        {
                            $$=new TreeNode(DeclarationKind.FUNCTION,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                            errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of semicolon");
                        }
                    |	function_head routine T_SEMI
                        {
                            $$=new TreeNode(DeclarationKind.FUNCTION,yyline);
                            $$.addChild($1);
                            $$.addChild($2);
                            errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of semicolon");
                        }
                    |	function_head routine
                        {
                            $$=new TreeNode(DeclarationKind.FUNCTION,yyline);
                            $$.addChild($1);
                            $$.addChild($2);
                            errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of semicolon");
                        }
                    ;
function_head       :   T_FUNCTION T_ID parameters  T_COLON simple_type_decl
                        {
                            $$=new TreeNode(DeclarationKind.FUNCTIONHEAD,yyline);
                            $$.setAttribute($2);
                            $$.addChild($3);
                            $$.addChild($5);
                        }
                    ;
parameters          :
                        {$$=null;}
                    |   T_LP para_decl_list T_RP
                        {$$=$2;}
                    ;
para_decl_list      :   para_decl_list  T_SEMI  para_type_list
                        {   TreeNode t=$1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($3);
                                $$=$1;
                            }
                            else
                                $$=$3;
                        }
                    |   para_type_list
                        {   $$=$1; }
                    ;
para_type_list      :   T_VAR name_list T_COLON simple_type_decl
                        {
                            $$=new TreeNode(DeclarationKind.VAR_PARA,yyline);
                            $$.addChild($2);
                            $$.addChild($4);
                        }
                    |   name_list T_COLON simple_type_decl
                        {
                            $$=new TreeNode(DeclarationKind.VAL_PARA,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                        }
                    ;
procedure_decl      :   procedure_head T_SEMI routine T_SEMI
                        {
                            $$=new TreeNode(DeclarationKind.PROCEDURE,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                        }
                    ;
procedure_head      :   T_PROCEDURE T_ID parameters
                        {
                            $$=new TreeNode(DeclarationKind.PROCEDUREHEAD,yyline);
                            $$.setAttribute($2);
                            $$.addChild($3);
                        }
                    ;
var_part            :
                        {   $$ = null;}
                    |   T_VAR var_decl_list
                        {   $$=$2;}
                    ;
var_decl_list       :   var_decl_list var_decl
                        {   TreeNode t = $1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($2);
                                $$=$1;
                            }
                            else
                                $$=$2;
                        }
                    |   var_decl    {$$=$1;}
                    ;
var_decl            :   name_list T_COLON type_decl T_SEMI
                        {   $$=new TreeNode(DeclarationKind.VAR,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                        }
                    |   name_list T_COLON type_decl
                        {   $$=new TreeNode(DeclarationKind.VAR,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                            errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of semicolon");
                        }
                    ;
const_part          :
                        {   $$ = null; }
                    |   T_CONST const_expr_list
                        {   $$=$2; }
                    ;
const_expr_list     :   const_expr_list const_expr
                        {
                            TreeNode t = $1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($2);
                                $$=$1;
                            }
                            else
                                $$=$2;
                        }

                    |   const_expr
                        {   $$=$1; }
                    ;
const_expr          :    ID T_EQUAL const_value T_SEMI
                        {
                            $$=new TreeNode(DeclarationKind.CONST,yyline);
                            $$.setAttribute($1.getAttribute());
                            $$.addChild($3);
                            $$.setExpType($3.getExpType());
                        }
                    |	ID T_EQUAL const_value
                        {
                            $$=new TreeNode(DeclarationKind.CONST,yyline);
                            $$.setAttribute($1.getAttribute());
                            $$.addChild($3);
                            $$.setExpType($3.getExpType());
                            errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of semicolon");
                        }
                    ;
const_value         :   T_INT
                        {
                            $$ =new TreeNode(ExpressionKind.CONST,yyline);
                            $$.setExpType(ExpressionType.INT);
                            $$.setAttribute($1);
                        }
                    |   T_REAL
                        {
                            $$ = new TreeNode(ExpressionKind.CONST,yyline);
                            $$.setExpType(ExpressionType.REAL);
                            $$.setAttribute($1);
                        }
                    |   T_CHAR
                        {
                            $$ = new TreeNode(ExpressionKind.CONST,yyline);
                            $$.setExpType(ExpressionType.CHAR);
                            $$.setAttribute($1.toCharArray());
                        }
                    |   T_STRING
                        {
                            $$ = new TreeNode(ExpressionKind.CONST,yyline);
                            $$.setExpType(ExpressionType.STRING);
                            $$.setAttribute($1);
                        }
                    |   T_TRUE
                        {
                            $$=new TreeNode(ExpressionKind.CONST,yyline);
                            $$.setExpType(ExpressionType.BOOL);
                            $$.setAttribute(1);
                        }
                    |   T_FALSE
                        {
                            $$=new TreeNode(ExpressionKind.CONST,yyline);
                            $$.setExpType(ExpressionType.BOOL);
                            $$.setAttribute(0);
                        }
                    |   T_MAXINT
                        {
                            $$=new TreeNode(ExpressionKind.CONST,yyline);
                            $$.setExpType(ExpressionType.INT);
                            $$.setAttribute(2147483647);
                        }
                    ;
type_part           :
                        {   $$=null;}
                    |   T_TYPE type_decl_list
                        {   $$=$2;}
                    ;
type_decl_list      :   type_decl_list  type_definition
                        {
                            TreeNode t=$1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($2);
                                $$=$1;
                            }
                            else
                              $$=$2;
                        }
                    |   type_definition
                        {   $$=$1;}
                    ;
type_definition     :   ID T_EQUAL type_decl T_SEMI
                        {   $$=new TreeNode(DeclarationKind.TYPE,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                        }
                    |   ID T_EQUAL type_decl
                        {   $$=new TreeNode(DeclarationKind.TYPE,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                            errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of semicolon");
                        }
                    ;
type_decl           :   simple_type_decl    {$$=$1;}
                    |   array_type_decl     {$$=$1;}
                    |   record_type_decl    {$$=$1;}
                    ;
record_type_decl    :   T_RECORD field_decl_list T_END
                        {   $$=$2; }
                    ;
field_decl_list     :   field_decl_list field_decl
                        {
                            TreeNode t=$1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($2);
                                $$=$1;
                            }
                            else
                                $$=$2;
                        }
                    |   field_decl {$$=$1;}
                    ;
field_decl          :   name_list T_COLON type_decl T_SEMI
                        {
                            $$=new TreeNode(TypeKind.RECORD,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                        }
                    |   name_list T_COLON type_decl
                        {
                            $$=new TreeNode(TypeKind.RECORD,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                            errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of semicolon");
                        }
                    ;
array_type_decl     :   T_ARRAY T_LB simple_type_decl T_RB T_OF type_decl
                        {
                            $$=new TreeNode(TypeKind.ARRAY,yyline);
                            $$.addChild($3);
                            $$.addChild($6);
                            $$.setExpType(ExpressionType.ARRAY);
                        }
                    ;
simple_type_decl    :   ID
                        {
                            $$=new TreeNode(TypeKind.SIMPLE_ID,yyline);
                            $$.setAttribute($1.getAttribute());
                            //free($1);
                        }
                    |   T_LP name_list T_RP
                        {   $$=new TreeNode(TypeKind.SIMPLE_ENUM,yyline);
                            $$.addChild($2);
                            $$.setExpType(ExpressionType.SIMPLE_ENUM);
                        }
                    |   const_value T_DOTDOT const_value
                        {   $$=new TreeNode(TypeKind.SIMPLE_LIMIT,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                            $$.setExpType(ExpressionType.SIMPLE_LIMIT);
                        }
                    |   T_MINUS const_value T_DOTDOT const_value
                        {
                            $$=new TreeNode(TypeKind.SIMPLE_LIMIT,yyline);
                            $$.addChild($2);
                            $$.getChildren().get(0).setAttribute(Integer.parseInt(String.valueOf($$.getChildren().get(0).getAttribute()))*(-1));
                            $$.addChild($4);
                            $$.setExpType(ExpressionType.SIMPLE_LIMIT);
                        }
                    |   T_MINUS const_value T_DOTDOT T_MINUS const_value
                        {   $$=new TreeNode(TypeKind.SIMPLE_LIMIT,yyline);
                            $$.addChild($2);
                            $$.getChildren().get(0).setAttribute(Integer.parseInt(String.valueOf($$.getChildren().get(0).getAttribute()))*(-1));
                            $$.addChild($5);
                            $$.getChildren().get(1).setAttribute(Integer.parseInt(String.valueOf($$.getChildren().get(1).getAttribute()))*(-1));
                            $$.setExpType(ExpressionType.SIMPLE_LIMIT);
                        }
                    |   ID T_DOTDOT ID
                        {
                            $$=new TreeNode(TypeKind.SIMPLE_LIMIT,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                            $$.setExpType(ExpressionType.SIMPLE_LIMIT);
                        }
                    |   T_INTEGER_TYPE
                        {   $$=new TreeNode(TypeKind.SIMPLE_SYS,yyline);
                            $$.setExpType(ExpressionType.INT);
                        }
                    |   T_BOOLEAN_TYPE
                        {   $$=new TreeNode(TypeKind.SIMPLE_SYS,yyline);
                            $$.setExpType(ExpressionType.BOOL);
                        }
                    |   T_REAL_TYPE
                        {   $$=new TreeNode(TypeKind.SIMPLE_SYS,yyline);
                            $$.setExpType(ExpressionType.REAL);
                        }
                    |   T_CHAR_TYPE
                        {   $$=new TreeNode(TypeKind.SIMPLE_SYS,yyline);
                            $$.setExpType(ExpressionType.CHAR);
                        }
                    ;
name_list           :   name_list T_COMMA ID
                        {
                            TreeNode t=$1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($3);
                                $$=$1;
                            }
                            else
                                $$=$3;
                        }
                    |   ID {   $$=$1; }
                    ;
ID                  :   T_ID
                        {   $$=new TreeNode(ExpressionKind.ID,yyline);
                            $$.setAttribute($1);
                        } ;
routine_body        :   compound_stmt   {$$=$1;} ;
compound_stmt       :   T_BEGIN stmt_list T_END {$$=$2;} 
					|	T_BEGIN stmt_list {$$=$2; errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of end");} ;
stmt_list           :
                        {$$=null;}
                    |   stmt_list stmt T_SEMI
                        {
                            TreeNode t=$1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($2);
                                $$=$1;
                            }
                            else
                                $$=$2;
                        }
                    |	stmt_list stmt
                        {
                            TreeNode t=$1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($2);
                                $$=$1;
                            }
                            else
                                $$=$2;
                           errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of semicolon");
                        }
                    ;
stmt                :   T_INT T_COLON no_label_stmt
                        {
                            $$=new TreeNode(StatementKind.LABEL,yyline);
                            $$.setAttribute($1);
                            $$.addChild($3);
                        }
                    |   no_label_stmt
                        {   $$=$1;}
                    ;
no_label_stmt       :   assign_stmt {$$=$1;}
                    |   compound_stmt   {$$=$1;}
                    |   goto_stmt   {$$=$1;}
                    |   if_stmt     {$$=$1;}
                    |   repeat_stmt {$$=$1;}
                    |   while_stmt  {$$=$1;}
                    |   case_stmt   {$$=$1;}
                    |   for_stmt    {$$=$1;}
                    |   proc_stmt   {$$=$1;};
assign_stmt         :   ID T_ASSIGN expression
                        {   $$=new TreeNode(StatementKind.ASSIGN,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                            $$.setAttribute(OperationKind.ID);
                        }
                    |   ID T_LB expression T_RB T_ASSIGN expression
                        {   $$=new TreeNode(StatementKind.ASSIGN,yyline);
                            $$.addChild($1);
                            ($$.getChildren().get(0)).addChild($3);
                            $$.addChild($6);
                            $$.setAttribute(OperationKind.ARRAY);
                        }
                    |
                        ID T_DOT ID T_ASSIGN expression
                        {   $$=new TreeNode(StatementKind.ASSIGN,yyline);
                            $$.addChild($1);
                            ($$.getChildren().get(0)).addChild($3);
                            $$.addChild($5);
                            $$.setAttribute(OperationKind.RECORD);
                        }
                    ;
goto_stmt           :   T_GOTO  T_INT
                        {   $$=new TreeNode(StatementKind.GOTO,yyline);
                            $$.setAttribute($2);
                        }
                    ;
if_stmt             :   T_IF expression T_THEN stmt  else_clause
                        {   $$=new TreeNode(StatementKind.IF,yyline);
                            $$.addChild($2);
                            $$.addChild($4);
                            $$.addChild($5);
                        }
                    |	T_IF expression  stmt  else_clause
                        {   $$=new TreeNode(StatementKind.IF,yyline);
                            $$.addChild($2);
                            $$.addChild($3);
                            $$.addChild($4);
                             errMsg.add("Error : error at line " + lex.getLineNumber() + ", lack of then");
                        }
                    ;
else_clause         :   {$$=null;}
                    |   T_ELSE  stmt    {$$=$2;}
                    ;
repeat_stmt         :   T_REPEAT stmt_list T_UNTIL expression
                        {
                            $$=new TreeNode(StatementKind.REPEAT,yyline);
                            $$.addChild($2);
                            $$.addChild($4);
                        }
                    |
                    ;
while_stmt          :   T_WHILE expression T_DO stmt
                        {   $$=new TreeNode(StatementKind.WHILE,yyline);
                            $$.addChild($2);
                            $$.addChild($4);
                        };
case_stmt           :   T_CASE expression T_OF case_expr_list T_END
                        {   $$=new TreeNode(StatementKind.CASE,yyline);
                            $$.addChild($2);
                            $$.addChild($4);
                        };
case_expr_list      :   case_expr_list  case_expr
                        {   TreeNode t=$1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($2);
                                $$=$1;
                            }
                            else
                                $$=$2;
                        }
                    |   case_expr   {$$=$1;};
case_expr           :   const_value T_COLON stmt T_SEMI
                        {
                            $$=new TreeNode(ExpressionKind.CASE,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                        }
                    |   ID  T_COLON stmt T_SEMI
                        {
                            $$=new TreeNode(ExpressionKind.CASE,yyline);
                            $$.addChild($1);
                            $$.addChild($3);
                        };
for_stmt            :   T_FOR ID T_ASSIGN expression T_TO expression T_DO stmt
                        {
                            $$=new TreeNode(StatementKind.FOR,yyline);
                            $$.addChild($2);
                            $$.addChild($4);
                            $$.addChild($6);
                            $$.addChild($8);
                            $$.setAttribute(OperationKind.TO);
                        }
                    |   T_FOR ID T_ASSIGN expression T_DOWNTO expression T_DO stmt
                        {
                            $$=new TreeNode(StatementKind.FOR,yyline);
                            $$.addChild($2);
                            $$.addChild($4);
                            $$.addChild($6);
                            $$.addChild($8);
                            $$.setAttribute(OperationKind.DOWNTO);
                        };
proc_stmt           :   ID
                        {   $$=new TreeNode(StatementKind.PROC_ID,yyline);
                            $$.setAttribute($1.getAttribute());
                        }
                    |   ID T_LP args_list T_RP
                        {   $$=new TreeNode(StatementKind.PROC_ID,yyline);
                            $$.setAttribute($1.getAttribute());
                            $$.addChild($3);
                        }
                    |   T_READ T_LP factor T_RP
                        {
                            $$=new TreeNode(StatementKind.PROC_SYS,yyline);
                            $$.setAttribute(OperationKind.READ);
                            $$.addChild($3);
                        }
                    |   T_WRITE T_LP args_list T_RP
                        {   $$=new TreeNode(StatementKind.PROC_SYS,yyline);
                            $$.setAttribute(OperationKind.WRITE);
                            $$.addChild($3);
                        }
                    |   T_WRITELN
                        {   $$=new TreeNode(StatementKind.PROC_SYS,yyline);
                            $$.setAttribute(OperationKind.WRITELN);
                        }
                    |   T_WRITELN T_LP args_list T_RP
                        {   $$=new TreeNode(StatementKind.PROC_SYS,yyline);
                            $$.setAttribute(OperationKind.WRITELN);
                            $$.addChild($3);
                        };
args_list           :   args_list T_COMMA expression
                        {   TreeNode t=$1;
                            if(t!=null){
                                while(t.getSibling()!=null)
                                  t=t.getSibling();
                                t.setSibling($3);
                                $$=$1;
                            }
                            else
                                $$=$3;
                        }
                    |   expression  {$$=$1;};

expression          :   expression T_GE expr {   $$=new TreeNode($1,$3,OperationKind.GE,yyline); }
                    |   expression T_GT expr {   $$=new TreeNode($1,$3,OperationKind.GT,yyline); }
                    |   expression T_LE expr {   $$=new TreeNode($1,$3,OperationKind.LE,yyline); }
                    |   expression T_LT expr {   $$=new TreeNode($1,$3,OperationKind.LT,yyline); }
                    |   expression T_EQUAL expr {   $$=new TreeNode($1,$3,OperationKind.EQUAL,yyline); }
                    |   expression T_UNEQUAL expr {  $$=new TreeNode($1,$3,OperationKind.UNEQUAL,yyline); }
                    |   expr {   $$=$1;} ;

expr                :   expr T_PLUS term  {   $$=new TreeNode($1,$3,OperationKind.PLUS,yyline); }
                    |   expr T_MINUS term  {  $$=new TreeNode($1,$3,OperationKind.MINUS,yyline); }
                    |   expr T_OR term  {     $$=new TreeNode($1,$3,OperationKind.OR,yyline); }
                    |   term {   $$=$1;} ;

term                :   term T_MUL factor {   $$=new TreeNode($1,$3,OperationKind.MUL,yyline); }
                    |   term T_DIV factor {   $$=new TreeNode($1,$3,OperationKind.DIV,yyline); }
                    |   term T_MOD factor {   $$=new TreeNode($1,$3,OperationKind.MOD,yyline); }
                    |   term T_AND factor {   $$=new TreeNode($1,$3,OperationKind.AND,yyline); }
                    |   factor {$$=$1;} ;

factor              :   ID
                        {$$=$1;}
                    |   ID T_LP args_list T_RP
                        {
                            $$=new TreeNode(ExpressionKind.FUNC_ID,yyline);
                            $$.setAttribute($1.getAttribute());
                            $$.addChild($3);
                        }
                    |   const_value {$$=$1;}
                    |   T_LP expression T_RP    {$$=$2;}
                    |   T_NOT factor
                        {
                           $$=new TreeNode($2,null,OperationKind.NOT,yyline);
                        }
                    |   T_MINUS factor
                        {   $$=new TreeNode($2, null, OperationKind.MINUS, yyline);
                        }
                    |   ID T_LB expression T_RB
                        {   $$=$1;
                            $$.addChild($3);
                            $$.setExpType(ExpressionType.ARRAY);
                        }
                    |   ID T_DOT ID
                        {   $$=$1;
                            $$.addChild($3);
                            $$.setExpType(ExpressionType.RECORD);
                        }
                    |   T_ABS T_LP args_list T_RP
                        {
                            $$=new TreeNode(OperationKind.ABS, $3,yyline);
                        }
                    |   T_CHR T_LP args_list T_RP
                        {
                            $$=new TreeNode(OperationKind.CHR, $3,yyline);
                        }
                    |   T_ODD T_LP args_list T_RP
                        {
                            $$=new TreeNode(OperationKind.ODD, $3,yyline);
                        }
                    |   T_ORD T_LP args_list T_RP
                        {

                            $$=new TreeNode(OperationKind.ORD, $3,yyline);
                        }
                    |   T_PRED T_LP args_list T_RP
                        {
                            $$=new TreeNode(OperationKind.PRED, $3,yyline);
                        }
                    |   T_SQR T_LP args_list T_RP
                        {
                            $$=new TreeNode(OperationKind.SQR, $3,yyline);
                        }
                    |   T_SQRT T_LP args_list T_RP
                        {
                            $$=new TreeNode(OperationKind.SQRT, $3,yyline);
                        }
                    |   T_SUCC T_LP args_list T_RP
                        {   $$=new TreeNode(OperationKind.SUCC, $3,yyline);
                        }
                    ;
%%

    private scanner lex;
    private TreeNode savedTree;
    private char[] savedName;
    private int savedNum;
    private int yyline;
    private static ArrayList<String> errMsg = new ArrayList<String>();

    private int yylex() {
        int retVal = -1;
        try {
            retVal = lex.yylex();
            yyline=lex.getLineNumber();
        } catch (IOException e) {
            System.err.println("IO Error:" + e);
        }
        return retVal;
    }

    /* error reporting */
    /* constructor taking in File Input */
    public Parser (Reader r) {
        lex = new scanner (r, this);
    }
    public TreeNode parse(){
        yyparse();
        return this.savedTree;
    }
    static boolean interactive;
    public static void main (String [] args) throws IOException {
      Parser yyparser;
      String filePath = args[0];
      yyparser = new Parser(new FileReader(filePath));
        System.err.println("GSDPASCAL Parse Started");
        TreeNode syntaxTree = yyparser.parse();
        
        if(errMsg.size() != 0){
        	for(String msg: errMsg){
        		System.err.println(msg);
        	}
        }
        System.err.println("GSDPASCAL Parse Error");
        if(errMsg.size() == 0 && syntaxTree != null){
            System.out.println(syntaxTree);
            syntaxTree.printTree(syntaxTree, 0);
        	CodeGenerator.getCodeGenerator().generate(syntaxTree);
        	System.err.println("GSDPASCAL Parse Finished");
      	}
    }

        /* error reporting */
    public void yyerror (String error) {
        System.err.println("Error : " + error + " at line " + lex.getLineNumber());
    }
