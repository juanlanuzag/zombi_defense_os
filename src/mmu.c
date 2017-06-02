/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"


void mmu_inicializar() {

	inicializar_kernel_mapping();

	proxima_pagina_libre = INICIO_PAGINAS_LIBRES;
}

void inicializar_kernel_mapping() {
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

void inicializar_con_identity_mapping(page_directory_entry* pde) {
	page_table_entry* pte = (page_table_entry*) mmu_proxima_pagina_fisica_libre();
	
	pde->p = 1;
	pde->rw = 1;
	pde->s = 1;  // Si esto se rompe es porque esta al reves este bit
	pde->pwt = 0;
	pde->pcd = 0;
	pde->a = 0;
	pde->i = 0;
	pde->ps = 0;
	pde->g = 0;
	pde->disp = 0;
	pde->base = ((int) pte) >> 12;

	int i;
	for (i=0; i < 1024 ; i++){
		pte[i].p = 1;
		pte[i].rw = 1;
		pte[i].s = 1;
		pte[i].pwt = 0;
		pte[i].pcd = 0;
		pte[i].a = 0;
		pte[i].d = 0;
		pte[i].pat = 0;
		pte[i].g = 0;
		pte[i].disp = 0;
		pte[i].base = i;
	}
}


unsigned int mmu_proxima_pagina_fisica_libre() {
	unsigned int pagina_libre = proxima_pagina_libre;
	proxima_pagina_libre += PAGE_SIZE;
	return pagina_libre;
}

#define PDE_INDEX(virtual) virtual >> 22
#define PTE_INDEX(virtual) (virtual << 10) >> 22
#define PG_READ_WRITE 1 
#define PG_USER 1
#define PG_PRESENT 0x00000001

void mmu_map_page(unsigned int virtual, unsigned int cr3, unsigned int fisica){
	page_directory_entry* page_dir = (page_directory_entry*) ((cr3 >> 3) << 3);

	page_table_entry* pte;
	if (page_dir[PDE_INDEX(virtual)].p){
		pte = (page_table_entry*) (page_dir[PDE_INDEX(virtual)].base << 12);
	} else {
		pte = (page_table_entry*) mmu_proxima_pagina_fisica_libre();
	}
	pte[PTE_INDEX(virtual)].p = 1;
	pte[PTE_INDEX(virtual)].rw = 1;
	pte[PTE_INDEX(virtual)].s = 1;
	pte[PTE_INDEX(virtual)].pwt = 0;
	pte[PTE_INDEX(virtual)].pcd = 0;
	pte[PTE_INDEX(virtual)].a = 0;
	pte[PTE_INDEX(virtual)].d = 0;
	pte[PTE_INDEX(virtual)].pat = 0;
	pte[PTE_INDEX(virtual)].g = 0;
	pte[PTE_INDEX(virtual)].disp = 0;
	pte[PTE_INDEX(virtual)].base = fisica >> 12;		
	tlbflush();
}

void mmu_unmap_page(unsigned int virtual, unsigned int cr3){
	page_directory_entry* page_dir = (page_directory_entry*) ((cr3 >> 3) << 3);
	page_table_entry* pte = (page_table_entry*) (page_dir[PDE_INDEX(virtual)].base << 12);
	pte[PTE_INDEX(virtual)].p = 0;
}


