#include <stdio.h>
#include "clob.h"
#include "btree.h"
#include "btree_val.h"
#include "unxs.h"
#include "mmod-auction.h"
#include "nifty.h"


int
main(void)
{
	clob_t c;
	qx_t tot[2U] = {0.dd, 0.dd};

	c = make_clob();
	clob_add(c, (clob_ord_t){CLOB_TYPE_MKT, CLOB_SIDE_LONG, {2.dd, 0.dd}});
	clob_add(c, (clob_ord_t){CLOB_TYPE_MKT, CLOB_SIDE_SHORT, {2.dd, 1.dd}});
	for (size_t j = 0U; j < 998U; j++) {
		clob_side_t s = rand() % 2;
		qx_t q = 2.dd + rand() % 4;
		tot[s] += q;
		clob_add(c, (clob_ord_t){CLOB_TYPE_LMT, s, {q, 0.dd}, .lmt = 100.00dd + rand() % 81});
	}

	clob_prnt(c);
	{
		mmod_auc_t auc = mmod_auction(c);
		btree_key_t a, b;

		unxs_auction(c, auc.prc, auc.qty);
		printf("AUC %f %f %f\n", (double)auc.prc, (double)auc.qty, (double)auc.imb);

		printf("TOT SUB %f %f\n", (double)tot[0], (double)tot[1]);
		btree_top(c.lmt[CLOB_SIDE_ASK], &a);
		btree_top(c.lmt[CLOB_SIDE_BID], &b);

#if 0
		qx_t q = 0.dd;
		for (size_t i = 0U; i < n; i++) {
			//q += x[i].x.qty;
			printf("%f @ %f  %u %u %f %zu  v  %u %u %f %zu\n",
			       (double)x[i].x.qty, (double)x[i].x.prc,
			       x[i].o[CLOB_SIDE_BUYER].typ, x[i].o[CLOB_SIDE_BUYER].sid, (double)x[i].o[CLOB_SIDE_BUYER].prc, x[i].o[CLOB_SIDE_BUYER].qid,
			       x[i].o[CLOB_SIDE_SELLER].typ, x[i].o[CLOB_SIDE_SELLER].sid, (double)x[i].o[CLOB_SIDE_SELLER].prc, x[i].o[CLOB_SIDE_SELLER].qid);
		}
		printf("TRA\t%f\t%f\t%zu\n", (double)x->x.prc, (double)q, n);
#endif
		printf("QUO\t%f\t%f\n", (double)b, (double)a);
	}
	clob_prnt(c);

	free_clob(c);
	return 0;
}
