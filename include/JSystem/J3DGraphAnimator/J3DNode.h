#ifndef J3DNODE_H
#define J3DNODE_H

class J3DNode;
typedef int (*J3DNodeCallBack)(J3DNode*, int);

class J3DNode {
public:
    virtual void init(Vec const& param_0, Mtx*);
    virtual void entryIn();
    virtual void calcIn();
    virtual u32 getType();
    virtual ~J3DNode();
    
    void appendChild(J3DNode*);

    J3DNode* getYounger() { return mYounger; }
    void setYounger(J3DNode* pYounger) { mYounger = pYounger; }
    void setCallBack(J3DNodeCallBack callback) { mCallBack = callback; }
    J3DNodeCallBack getCallBack() { return mCallBack; }
    J3DNode* getChild() { return mChild; }

    /* 0x00 */ void* mCallBackUserData;
    /* 0x04 */ J3DNodeCallBack mCallBack;
    /* 0x08 */ void* field_0x8;
    /* 0x0C */ J3DNode* mChild;
    /* 0x10 */ J3DNode* mYounger;
};  // Size: 0x14

#endif /* J3DNODE_H */
