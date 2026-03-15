#pragma once
#define __ENV_GODOT_API_TYPE_VARIANT__
#include "pkg.h"

#define package gde_Type_Variant

typefrom(u32, Type);
/* VARIANT TYPES */
#define VarientTypes		\
values(TypeID, u32,		\
	NIL, 			\
	INT,			\
				\
	FLOAT,   		\
	STRING,			\
				\
	VECTOR2, 		\
	VECTOR2I,		\
	RECT2,			\
	RECT2I,			\
	VECTOR3,		\
	VECTOR3I,		\
	TRANSFORM2D,		\
	VECTOR4,		\
	VECTOR4I,		\
	PLANE,			\
	QUATERNION,		\
	AABB,			\
	BASIS,			\
	TRANSFORM3D,		\
	PROJECTION,		\
				\
	COLOR,			\
	STRING_NAME,		\
	NODE_PATH,		\
	RID,			\
	OBJECT,			\
	CALLABLE,		\
	SIGNAL,			\
	DICTIONARY,		\
	ARRAY,			\
				\
	PACKED_BYTE_ARRAY,	\
	PACKED_INT32_ARRAY,	\
	PACKED_INT64_ARRAY,	\
	PACKED_FLOAT32_ARRAY,	\
	PACKED_FLOAT64_ARRAY,	\
	PACKED_STRING_ARRAY,	\
	PACKED_VECTOR2_ARRAY,	\
	PACKED_VECTOR3_ARRAY,	\
	PACKED_COLOR_ARRAY,	\
	PACKED_VECTOR4_ARRAY)	


typefrom(u32, Op);
#define VariantOp	\
values(OpID, u32,	\
	EQUAL,		\
	NOT_EQUAL,	\
	LESS,		\
	LESS_EQUAL,	\
	GREATER,	\
	GREATER_EQUAL,	\
			\
	ADD,		\
	SUBTRACT,	\
	MULTIPLY,	\
	DIVIDE,		\
	NEGATE,		\
	POSITIVE,	\
	MODULE,		\
	POWER,		\
			\
	SHIFT_LEFT,	\
	SHIFT_RIGHT,	\
	BIT_AND,	\
	BIT_OR,		\
	BIT_XOR,	\
	BIT_NEGATE,	\
			\
	AND,		\
	OR,		\
	XOR,		\
	NOT,		\
			\
	IN,		\
	MAX)		

typefrom(pntr, 		Ptr);
typefrom(constpntr,  	ConstPtr);
typefrom(pntr, 		UninitPtr);

type_fn(void,	FromTypeConstructor,	pkg(UninitPtr), gde_Type_Ptr);
type_fn(void*,	GetInternalPtr,		pkg(Ptr));
type_fn(void,	ConstructorToType,	gde_Type_UninitPtr, pkg(Ptr));


type_fn(void,	Ptr_OpEval,		pkg(ConstPtr) ,        pkg(ConstPtr) ,  pkg(Ptr) );
type_fn(void,	Ptr_BuiltInMethod,		pkg(Ptr) ,       const pkg(ConstPtr)*,  pkg(Ptr), int);
type_fn(void,	Ptr_Constructor,		pkg(UninitPtr) , const pkg(ConstPtr)*);
type_fn(void,	Ptr_Destructor,			pkg(Ptr));
type_fn(void,	Ptr_Setter,			pkg(Ptr) , 	pkg(ConstPtr));
type_fn(void,	Ptr_Getter,			pkg(ConstPtr),  pkg(Ptr));
type_fn(void,	Ptr_IndexedSetter,		pkg(Ptr), 	gde_Int, 	 pkg(ConstPtr));
type_fn(void,	Ptr_IndexedGetter,		pkg(ConstPtr),  gde_Int, 	 pkg(Ptr));
type_fn(void,	Ptr_KeyedSetter,		pkg(Ptr), 	pkg(ConstPtr),   pkg(ConstPtr));
type_fn(void,	Ptr_KeyedGetter,		pkg(ConstPtr),  pkg(ConstPtr),   pkg(Ptr));
type_fn(u32, 	Ptr_KeyedChecker,		pkg(ConstPtr), 	pkg(ConstPtr));
type_fn(void, 	Ptr_UtilityFunction,	gde_Ptr, 	  const gde_ConstPtr*,  int);

#undef package
