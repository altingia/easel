/* 
 * Digital representation of biosequence symbols in Easel.
 * SVN $Id$
 * SRE, Tue Nov 23 19:44:01 2004 [St. Louis]
 */
#ifndef ESL_ALPHABET_INCLUDED
#define ESL_ALPHABET_INCLUDED

/* Flags for alphabet types.
 */
#define eslUNKNOWN     0 /* 0=unknown is easel-wide convention; don't change */
#define eslRNA         1
#define eslDNA         2		
#define eslAMINO       3		
#define eslNONSTANDARD 4

/* Value of sentinel bytes (0 and L+1) in a dsq.
 */
#define eslSENTINEL    127

typedef struct {
  int    type;		 /* eslDNA, eslRNA, eslAMINO, or eslNONSTANDARD     */
  int    K;		 /* uniq alphabet size: 4 or 20                     */
  int    Kp;		 /* total size: alphabet + degen + gap + missing    */
  char  *sym;            /* "ACGTRYMKSWHBVDN-~", for instance    [0..Kp-1]  */
  int    inmap[128];     /* inmap['A'] = 0, etc: dsq[] index for a symbol   */
  char **degen;          /* 1/0, which syms inc which res [0..Kp-3][0..K-1] */
  int   *ndegen;	 /* # of degenerate residues per code  [0..Kp-3]    */
} ESL_ALPHABET;


/* 1. An ESL_ALPHABET object.
 */
extern ESL_ALPHABET *esl_alphabet_Create(int type);
extern ESL_ALPHABET *esl_alphabet_CreateCustom(char *alphabet, int K, int Kp);
extern int           esl_alphabet_SetSynonym(ESL_ALPHABET *a, char sym, char c);
extern int           esl_alphabet_SetCaseInsensitive(ESL_ALPHABET *a);
extern int           esl_alphabet_SetDegeneracy(ESL_ALPHABET *a, char c, char *ds);
extern void          esl_alphabet_Destroy(ESL_ALPHABET *a);

/* 2. Digitized sequences.
 */
extern int esl_dsq_Create(ESL_ALPHABET *a, char *seq, int L, char **ret_dsq);
extern int esl_dsq_Set   (ESL_ALPHABET *a, char *seq, int L, char *dsq);

/* 3. Other routines in the API.
 */
extern int    esl_abc_IAvgScore(ESL_ALPHABET *a, char x, int *sc);
extern float  esl_abc_FAvgScore(ESL_ALPHABET *a, char x, float *sc);
extern double esl_abc_DAvgScore(ESL_ALPHABET *a, char x, double *sc);
extern int    esl_abc_IExpectScore(ESL_ALPHABET *a, char x, int *sc, float *p);
extern float  esl_abc_FExpectScore(ESL_ALPHABET *a, char x, float *sc,
				   float *p);
extern double esl_abc_DExpectScore(ESL_ALPHABET *a, char x, double *sc,
				   double *p);

extern int    esl_abc_IAvgScVec(ESL_ALPHABET *a, int *sc);
extern int    esl_abc_FAvgScVec(ESL_ALPHABET *a, float *sc);
extern int    esl_abc_DAvgScVec(ESL_ALPHABET *a, double *sc);
extern int    esl_abc_IExpectScVec(ESL_ALPHABET *a, int *sc, float *p);
extern int    esl_abc_FExpectScVec(ESL_ALPHABET *a, float *sc, float *p);
extern int    esl_abc_DExpectScVec(ESL_ALPHABET *a, double *sc, double *p);
extern int    esl_abc_FCount(ESL_ALPHABET *abc, float *ct, int x, float wt);
extern int    esl_abc_DCount(ESL_ALPHABET *abc, double *ct, int x, double wt);
extern char  *esl_abc_Type(int type);

#define esl_abc_DigitizeSymbol(a, c) ((char) a->inmap[(int)c])
#define esl_abc_XIsDegenerate(a, x)  ((x) > a->K && (x) < a->Kp)
#define esl_abc_XIsBasic(a, x)       ((x) >= 0   && (x) < a->K)
#define esl_abc_XIsGap(a, x)         ((x) == a->K)

#define esl_abc_CIsDegenerate(a, c)  ((a->inmap[c]) > a->K && (a->inmap[c]) < a->Kp)
#define esl_abc_CIsBasic(a, c)       ((a->inmap[c]) >= 0   && (a->inmap[c]) < a->K)
#define esl_abc_CIsGap(a, c)         ((a->inmap[c]) == a->K)

#endif /*!ESL_ALPHABET_INCLUDED*/

/*****************************************************************
 * @LICENSE@
 *****************************************************************/
