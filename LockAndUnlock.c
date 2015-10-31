/**********************************************************************
* 版权所有 (C)2015, Zhou Zhaoxiong。
*
* 文件名称：LockAndUnlock.c
* 文件标识：无
* 内容摘要：演示加锁与解锁函数的调用
* 其它说明：无
* 当前版本：V1.0
* 作    者：Zhou Zhaoxiong
* 完成日期：20150509
*
**********************************************************************/
#include <sys/time.h>
#include <pthread.h>

// 宏定义
#define LOCKTIMEOUT    5000       // 互斥量超时时长为5000毫秒

// 全局变量
pthread_mutex_t g_Mutex;

// 重定义数据类型
typedef signed   int    INT32;

// 函数声明
INT32 MutexLock();
INT32 MutexUnLock();


/**********************************************************************
* 功能描述：主函数
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：无
* 修改日期        版本号      修改人              修改内容
* ---------------------------------------------------------------
* 20150509        V1.0     Zhou Zhaoxiong          创建
***********************************************************************/
INT32 main()
{
    INT32 iRetCode = 0;

    iRetCode = MutexLock();      // 互斥量加锁
    if (iRetCode < 0)
    {
        printf("exec MutexLock failed!\n");
        return -1;
    }

    printf("--------------\n");
    printf("Add code here!\n");
    printf("--------------\n");

    iRetCode = MutexUnLock();   // 互斥量解锁
    if (iRetCode < 0)
    {
        printf("exec MutexUnLock failed!\n");
        return -1;
    }

    return 0;
}


/**********************************************************************
* 功能描述： 互斥量加锁
* 输入参数： 无
* 输出参数： 无
* 返 回 值： 0-成功    -1-失败
* 其它说明： 无
* 修改日期      版本号       修改人        修改内容
* ------------------------------------------------------------------
* 20150509       V1.0     Zhou Zhaoxiong     创建
********************************************************************/  
INT32 MutexLock()
{
    struct timeval  tCurrentTime;
    struct timespec tTimeout;

    INT32 iRetCode = 0;

    gettimeofday(&tCurrentTime, NULL);                              // 获取当前绝对时间
    tTimeout.tv_sec  = tCurrentTime.tv_sec + LOCKTIMEOUT/1000;      // 指定超时时间
    tTimeout.tv_nsec = tCurrentTime.tv_usec * 1000;

    iRetCode = pthread_mutex_timedlock(&g_Mutex, &tTimeout);
    if (iRetCode != 0)
    {
        printf("MutexLock: exec pthread_mutex_timedlock failed, RetCode=%d\n", iRetCode);
        return -1;
    }

    return 0;
}


/**********************************************************************
* 功能描述： 互斥量解锁
* 输入参数： 无
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 无
* 修改日期      版本号       修改人        修改内容
* ------------------------------------------------------------------
* 20150509       V1.0     Zhou Zhaoxiong     创建
********************************************************************/
INT32 MutexUnLock()
{
    INT32 iRetCode = 0;

    iRetCode = pthread_mutex_unlock(&g_Mutex);
    if (iRetCode != 0)
    {
        printf("MutexUnLock: exec pthread_mutex_unlock failed, RetCode=%d\n", iRetCode);
        return -1;
    }

    return 0;
}
