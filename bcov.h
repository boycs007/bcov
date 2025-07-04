#ifndef BCOV_H
#define BCOV_H

#ifdef __cplusplus
extern "C" {
#endif

void __gcov_dump(void);
void __gcov_reset(void);

#ifdef __cplusplus
}
#endif

void InitChildCoverage();

#endif  // BCOV_H