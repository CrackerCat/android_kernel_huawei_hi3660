#ifndef INT_BLK_MQ_H
#define INT_BLK_MQ_H

#include "blk-stat.h"
#include "hisi-blk.h"

struct blk_mq_tag_set;

struct blk_mq_ctx {
	struct {
		spinlock_t		lock;
		struct list_head	rq_list;
	}  ____cacheline_aligned_in_smp;

	unsigned int		cpu;
	unsigned int		index_hw;

	/* incremented at dispatch time */
	unsigned long		rq_dispatched[2];
	unsigned long		rq_merged;

	/* incremented at completion time */
	unsigned long		____cacheline_aligned_in_smp rq_completed[2];
#ifdef CONFIG_WBT
	struct blk_rq_stat	stat[4];
#endif

	struct request_queue	*queue;
	struct kobject		kobj;
} ____cacheline_aligned_in_smp;

void blk_mq_run_hw_queue(struct blk_mq_hw_ctx *hctx, bool async);
void blk_mq_freeze_queue(struct request_queue *q);
void blk_mq_free_queue(struct request_queue *q);
int blk_mq_update_nr_requests(struct request_queue *q, unsigned int nr);
void blk_mq_wake_waiters(struct request_queue *q);

/*
 * CPU hotplug helpers
 */
void blk_mq_enable_hotplug(void);
void blk_mq_disable_hotplug(void);

/*
 * CPU -> queue mappings
 */
int blk_mq_map_queues(struct blk_mq_tag_set *set);
extern int blk_mq_hw_queue_to_node(unsigned int *map, unsigned int);

static inline struct blk_mq_hw_ctx *blk_mq_map_queue(struct request_queue *q,
		int cpu)
{
	return q->queue_hw_ctx[q->mq_map[cpu]];
}

/*
 * sysfs helpers
 */
extern void blk_mq_sysfs_init(struct request_queue *q);
extern int blk_mq_sysfs_register(struct request_queue *q);
extern void blk_mq_sysfs_unregister(struct request_queue *q);
extern void blk_mq_hctx_kobj_init(struct blk_mq_hw_ctx *hctx);

extern void blk_mq_rq_timed_out(struct request *req, bool reserved);

void blk_mq_release(struct request_queue *q);

static inline struct blk_mq_ctx *__blk_mq_get_ctx(struct request_queue *q,
					   unsigned int cpu)
{
	return per_cpu_ptr(q->queue_ctx, cpu);
}

/*
 * This assumes per-cpu software queueing queues. They could be per-node
 * as well, for instance. For now this is hardcoded as-is. Note that we don't
 * care about preemption, since we know the ctx's are persistent. This does
 * mean that we can't rely on ctx always matching the currently running CPU.
 */
static inline struct blk_mq_ctx *blk_mq_get_ctx(struct request_queue *q)
{
	return __blk_mq_get_ctx(q, get_cpu());
}

static inline void blk_mq_put_ctx(struct blk_mq_ctx *ctx)
{
#ifdef CONFIG_HISI_BLK
	int ret = -EPERM;
	if (ctx->queue->hisi_queue_ops && ctx->queue->hisi_queue_ops->mq_ctx_put_fn)
		ret = ctx->queue->hisi_queue_ops->mq_ctx_put_fn(ctx);
	if (ret) {
		if (likely(ret == -EPERM)) {
			put_cpu();
		} else {
			pr_err("%s: mq_ctx_put_fn failed. err = %d \r\n", __func__, ret);
		}
	}
#else
	put_cpu();
#endif
}

struct blk_mq_alloc_data {
	/* input parameter */
	struct request_queue *q;
#ifdef CONFIG_HISI_BLK
	unsigned long io_flag;
#endif
	unsigned int flags;

	/* input & output parameter */
	struct blk_mq_ctx *ctx;
	struct blk_mq_hw_ctx *hctx;
};

static inline void blk_mq_set_alloc_data(struct blk_mq_alloc_data *data,
		struct request_queue *q, unsigned int flags,
		struct blk_mq_ctx *ctx, struct blk_mq_hw_ctx *hctx)
{
	data->q = q;
	data->flags = flags;
	data->ctx = ctx;
	data->hctx = hctx;
}

static inline bool blk_mq_hw_queue_mapped(struct blk_mq_hw_ctx *hctx)
{
	return hctx->nr_ctx && hctx->tags;
}

#ifdef CONFIG_WBT
void blk_mq_stat_add(struct request *rq);
#endif
#endif
