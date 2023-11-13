/*
 * global.h
 *
 *  Created on: Nov 1, 2023
 *      Author: Vy Nguyen
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define INIT		0
#define MODE_1		1
#define MODE_2		2
#define MODE_3		3
#define MODE_4		4

#define RED1_GREEN2       10
#define RED1_YELLOW2      11
#define GREEN1_RED2       12
#define YELLOW1_RED2      13

#define	AUTO_RED		21
#define AUTO_YELLOW		22
#define AUOTO_GREEN		23

#define INC_RED			31
#define INC_YELLOW		32
#define INC_GREEN		33

extern int status;
extern int PERIOD_RED;
extern int PERIOD_YELLOW;
extern int PERIOD_GREEN;

#endif /* INC_GLOBAL_H_ */
