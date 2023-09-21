#include "redismodule.h"
#include <stdlib.h>

/*
* example.HGETSET <key> <element> <value>
* Atomically set a value in a HASH key to <value> and return its value before
* the HSET.
*
* Basically atomic HGET + HSET
*/
int HGetSetCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
	if (argc != 4) {
		return RedisModule_WrongArity(ctx);
	}

	RedisModule_AutoMemory(ctx);

	// https://github.com/redis/redis/blob/HEAD/src/module.c#L6158
	RedisModuleCallReply *rep = RedisModule_Call(ctx, "HGET", "ss", argv[1], argv[2]);

	if (RedisModule_CallReplyType(rep) == REDISMODULE_REPLY_ERROR) {
		RedisModule_ReplyWithCallReply(ctx, rep);
		return REDISMODULE_ERR;
	}

	RedisModuleCallReply *srep = RedisModule_Call(ctx, "HSET", "sss", argv[1], argv[2], argv[3]);
	if (RedisModule_CallReplyType(srep) == REDISMODULE_REPLY_ERROR) {
		RedisModule_ReplyWithCallReply(ctx, srep);
		return REDISMODULE_ERR;
	}

	RedisModule_ReplyWithCallReply(ctx, rep);
	return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (RedisModule_Init(ctx,"example2",1,REDISMODULE_APIVER_1)
        == REDISMODULE_ERR) return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"example2.hgetset",HGetSetCommand, "write", 1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    return REDISMODULE_OK;
}
