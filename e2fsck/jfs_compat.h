
#ifndef _JFS_COMPAT_H
#define _JFS_COMPAT_H

#include "e2fsck.h"
#include <errno.h>

#define printk printf
#define KERN_ERR ""
#define KERN_DEBUG ""

#define READ 0
#define WRITE 1

typedef int tid_t;
typedef e2fsck_t kdev_t;
typedef struct journal_s journal_t;

struct buffer_head {
	char	 b_data[8192];
	e2fsck_t b_ctx;
	io_channel b_io;
	int	 b_size;
	blk_t	 b_blocknr;
	int	 b_dirty;
	int	 b_uptodate;
	int	 b_err;
};

struct inode {
	e2fsck_t i_ctx;
	ino_t	 i_ino;
	struct ext2_inode i_ext2;
};

int bmap(struct inode *inode, int block);
struct buffer_head *getblk(e2fsck_t ctx, blk_t blocknr, int blocksize);
void ll_rw_block(int rw, int dummy, struct buffer_head *bh);
void mark_buffer_dirty(struct buffer_head *bh, int dummy);
void brelse(struct buffer_head *bh);
int buffer_uptodate(struct buffer_head *bh);
void wait_on_buffer(struct buffer_head *bh);
#define fsync_dev(dev) do {} while(0)
#define buffer_req(bh) 1
#define do_readahead(journal, start) do {} while(0)
#define J_ASSERT(assert)						\
	do { if (!(assert)) {						\
		printf ("Assertion failure in %s() at %s line %d: "	\
			"\"%s\"\n",					\
			__FUNCTION__, __FILE__, __LINE__, # assert);	\
		exit(FSCK_ERROR);					\
	} } while (0)

#endif /* _JFS_COMPAT_H */
