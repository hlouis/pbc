#ifndef PROTOBUF_C_MAP_H
#define PROTOBUF_C_MAP_H

struct map_ip;		//!< map with number key
struct map_si;		//!< map with string key
struct map_sp;		//!< map with string key and more iteration function

/**
 * map key value type
 */
struct map_kv {
	int id;
	void *pointer;
};

struct map_si * _pbcM_si_new(struct map_kv * table, int size);
int _pbcM_si_query(struct map_si *map, const char *key);
void _pbcM_si_delete(struct map_si *map);

struct map_ip * _pbcM_ip_new(struct map_kv * table, int size);
struct map_ip * _pbcM_ip_combine(struct map_ip * a, struct map_ip * b);
void * _pbcM_ip_query(struct map_ip * map, int id);
void _pbcM_ip_delete(struct map_ip *map);

struct map_sp * _pbcM_sp_new(void);
void _pbcM_sp_insert(struct map_sp *map, const char *key, void * value);
void * _pbcM_sp_query(struct map_sp *map, const char *key);
void ** _pbcM_sp_query_insert(struct map_sp *map, const char *key);
void _pbcM_sp_delete(struct map_sp *map);
void _pbcM_sp_foreach(struct map_sp *map, void (*func)(void *p));
void _pbcM_sp_foreach_ud(struct map_sp *map, void (*func)(void *p, void *ud), void *ud);
void * _pbcM_sp_next(struct map_sp *map, const char ** key);

#endif
