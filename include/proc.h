#ifndef GUARD_PROC_H
#define GUARD_PROC_H

struct Proc;

typedef void (*ProcFunc)(struct Proc *);

struct ProcCmd
{
    s16 opcode;
    s16 dataImm;
    void *dataPtr;
};

#define PROC_END                                     { 0x00, 0x0000, 0 }
#define PROC_SET_NAME(aName)                         { 0x01, 0x0000, aName }
#define PROC_CALL_ROUTINE(apRoutine)                 { 0x02, 0x0000, (void*)(apRoutine) }
#define PROC_LOOP_ROUTINE(apRoutine)                 { 0x03, 0x0000, (void*)(apRoutine) }
#define PROC_SET_DESTRUCTOR(apRoutine)               { 0x04, 0x0000, (void*)(apRoutine) }
#define PROC_NEW_CHILD(ap6CChild)                    { 0x05, 0x0000, (void*)(ap6CChild) }
#define PROC_NEW_CHILD_BLOCKING(ap6CChild)           { 0x06, 0x0000, (void*)(ap6CChild) }
#define PROC_NEW_MAIN_BUGGED(ap6CMain)               { 0x07, 0x0000, ap6CMain }
#define PROC_WHILE_EXISTS(ap6CToCheck)               { 0x08, 0x0000, (void*)(ap6CToCheck) }
#define PROC_END_ALL(ap6CToCheck)                    { 0x09, 0x0000, (void*)(ap6CToCheck) }
#define PROC_BREAK_ALL_LOOP(ap6CToCheck)             { 0x0A, 0x0000, (void*)(ap6CToCheck) }
#define PROC_LABEL(aLabelId)                         { 0x0B, aLabelId, 0 }
#define PROC_GOTO(aLabelId)                          { 0x0C, aLabelId, 0 }
#define PROC_JUMP(ap6CCode)                          { 0x0D, 0x0000, (void*)(ap6CCode) }
#define PROC_SLEEP(aTime)                            { 0x0E, aTime,  0 }
#define PROC_SET_MARK(aMark)                         { 0x0F, aMark,  0 }
#define PROC_BLOCK                                   { 0x10, 0x0000, 0 }
#define PROC_END_IF_DUPLICATE                        { 0x11, 0x0000, 0 }
#define PROC_SET_BIT4                                { 0x12, 0x0000, 0 }
#define PROC_13                                      { 0x13, 0x0000, 0 }
#define PROC_WHILE_ROUTINE(aprRoutine)               { 0x14, 0x0000, (void*)(aprRoutine) }
#define PROC_15                                      { 0x15, 0x0000, 0 }
#define PROC_CALL_ROUTINE_2(aprRoutine)              { 0x16, 0x0000, (void*)(aprRoutine) }
#define PROC_END_DUPLICATES                          { 0x17, 0x0000, 0 }
#define PROC_CALL_ROUTINE_ARG(aprRoutine, aArgument) { 0x18, aArgument, (void*)(aprRoutine) }
#define PROC_19                                      { 0x19, 0x0000, 0 }
#define PROC_YIELD                                   PROC_SLEEP(0)

struct Proc
{
    /*0x00*/ struct ProcCmd *script;  // pointer to process script
    /*0x04*/ struct ProcCmd *currCmd;  // pointer to currently executing script command
    /*0x08*/ ProcFunc onDelete;  // callback to run upon delegint the process
    /*0x0C*/ ProcFunc nativeFunc;  // callback to run once each frame.
                                   // disables script execution when not null
    /*0x10*/ char *name;
    /*0x14*/ struct Proc *parent;  // pointer to parent proc. If this proc is a root proc,
                                   // this member is an integer which is the root index.
    /*0x18*/ struct Proc *child;  // pointer to most recently added child
    /*0x1C*/ struct Proc *next;  // next sibling
    /*0x20*/ struct Proc *prev;  // previous sibling
    /*0x24*/ s16 sleepTime;
    /*0x26*/ u8 mark;
    /*0x27*/ u8 flags;
    /*0x28*/ u8 blockSemaphore;  // wait semaphore. Process execution is blocked when this is nonzero.
    /*0x29*/ u8 filler29[0x6C-0x29];
};

struct UnknownProcStruct
{
    struct Proc *unk0;
    struct ProcCmd *unk4;
    int unk8;
};

void Proc_Initialize(void);
// ??? Proc_Create(???);
// ??? Proc_CreateBlockingChild(???);
// ??? Proc_Delete(???);;
// ??? Proc_Run(???);
// ??? Proc_ClearNativeCallback(???);
// ??? Proc_Find(???);
// ??? Proc_FindNonBlocked(???);
// ??? Proc_FindWithMark(???);
// ??? Proc_GotoLabel(???);
// ??? Proc_JumpToPointer(???);
// ??? Proc_SetMark(???);
// ??? Proc_SetDestructor(???);
// ??? Proc_ForEach(???);
// ??? Proc_ForEachWithScript(???);
// ??? Proc_ForEachWithMark(???);
// ??? Proc_BlockEachWithMark(???);
// ??? Proc_UnblockEachWithMark(???);
// ??? Proc_DeleteEachWithMark(???);
// ??? Proc_DeleteAllWithScript(???);
// ??? Proc_ClearNativeCallbackEachWithScript(???);
// ??? sub_80030CC(???);
// ??? sub_800344C(???);
// ??? Proc_SetNativeFunc(???);
// ??? Proc_BlockSemaphore(???);
// ??? Proc_WakeSemaphore(???);
// ??? Proc_FindAfter(???);
// ??? Proc_FindAfterWithParent(???);
// ??? sub_80034D4(???);
// ??? sub_80034FC(???);
// ??? sub_8003530(???);
// ??? sub_8003540(???);

#endif  // GUARD_PROC_H