#include <stdio.h>
#include "clob.h"
#include "unxs.h"
#include "mmod-auction.h"
#include "nifty.h"


int
main(void)
{
	clob_t c;

	c = make_clob();

	/* cloe fuckup 1 */
	clob_add(c, (clob_ord_t){TYPE_LMT, SIDE_ASK, {0.dd, 0.0dd}, .lmt = 2.85dd});
	clob_add(c, (clob_ord_t){TYPE_MKT, SIDE_BID, {1400.dd, 0.0dd}});

	clob_prnt(c);

	mmod_auc_t auc = mmod_auction(c);
	printf("AUCTION %f @ %f ~%f\n", (double)auc.qty, (double)auc.prc, (double)auc.imb);

	free_clob(c);
	return auc.prc != 2.85dd || auc.qty != 0.dd || auc.imb != 1400.dd;
}
