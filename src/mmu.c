/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

void mmu_inicializar() {
	page_directory_entry* dir_pagina_kernel = (page_directory_entry*) 0x27000;
	page_table_entry* dir_table_kernel = (page_table_entry*) 0x28000;
	dir_pagina_kernel->p = 1;
	dir_pagina_kernel->rw = 1;
	dir_pagina_kernel->s = 0;
	dir_pagina_kernel->pwt = 0;
	dir_pagina_kernel->pcd = 0;
	dir_pagina_kernel->a = 0;
	dir_pagina_kernel->i = 0;
	dir_pagina_kernel->ps = 0;
	dir_pagina_kernel->g = 0;
	dir_pagina_kernel->disp = 0;
	dir_pagina_kernel->base = 0x28;

	int i;
	for (i=0; i < 1024 ; i++){
		dir_table_kernel[i].p = 1;
		dir_table_kernel[i].rw = 1;
		dir_table_kernel[i].s = 0;
		dir_table_kernel[i].pwt = 0;
		dir_table_kernel[i].pcd = 0;
		dir_table_kernel[i].a = 0;
		dir_table_kernel[i].d = 0;
		dir_table_kernel[i].pat = 0;
		dir_table_kernel[i].g = 0;
		dir_table_kernel[i].disp = 0;
		dir_table_kernel[i].base = i;
	}

}







