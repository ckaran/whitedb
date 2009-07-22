/*
* $Id:  $
* $Version: $
*
* Copyright (c) Tanel Tammet 2004,2005,2006,2007,2008,2009
*
* Contact: tanel.tammet@gmail.com                 
*
* This file is part of wgandalf
*
* Wgandalf is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Wgandalf is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Wgandalf.  If not, see <http://www.gnu.org/licenses/>.
*
*/

 /** @file dbdata.h
 * Datatype encoding defs and public headers for actual data handling procedures.
 */

#ifndef __defined_dbdata_h
#define __defined_dbdata_h

#ifdef _WIN32
#include "../config-w32.h"
#else
#include "../config.h"
#endif
#include "dballoc.h"

// ============= api part starts ================


/* ---  built-in data type numbers ----- */

/* the built-in data types are primarily for api purposes.
   internally, some of these types like int, str etc have several 
   different ways to encode along with different bit masks 
*/   


#define WG_NULLTYPE 1
#define WG_RECORDTYPE 2
#define WG_INTTYPE 3
#define WG_DOUBLETYPE 4
#define WG_STRTYPE 5
#define WG_XMLLITERALTYPE 6
#define WG_URITYPE 7
#define WG_BLOBTYPE 8
#define WG_CHARTYPE 9
#define WG_DATETYPE 10
#define WG_TIMETYPE 11
#define WG_ANONCONSTTYPE 12
#define WG_VARTYPE 13

/* ---  internal data type numbers ----- */

/* internal data types are used for encoding type in datarec and longstr objects */

/*
#define WG_NULLTYPE 1
#define WG_RECORDTYPE 2
#define WG_INTTYPE 3
#define WG_DOUBLETYPE 4
#define WG_STRTYPE 5
#define WG_XMLLITERALTYPE 6
#define WG_URITYPE 7
#define WG_BLOBTYPE 8
#define WG_CHARTYPE 9
#define WG_DATETYPE 10
#define WG_TIMETYPE 11
#define WG_ANONCONSTTYPE 12
#define WG_VARTYPE 13
*/

/* prototypes of wg database api functions 

*/

typedef int wg_int;


/* -------- creating and scanning records --------- */

void* wg_create_record(void* db, wg_int length); ///< returns NULL when error, ptr to rec otherwise
void* wg_delete_record(void* db, wg_int);  ///< returns NULL when error, any other otherwise

void* wg_get_first_record(void* db);              ///< returns NULL when error or no recs
void* wg_get_next_record(void* db, void* record); ///< returns NULL when error or no more recs

/* -------- setting and fetching record field values --------- */

wg_int wg_get_record_len(void* db, void* record); ///< returns negative int when error
wg_int* wg_get_record_dataarray(void* db, void* record); ///< pointer to record data array start

// following field setting functions return negative int when err, 0 when ok
wg_int wg_set_field(void* db, void* record, wg_int fieldnr, wg_int data); 

wg_int wg_set_int_field(void* db, void* record, wg_int fieldnr, wg_int data); 
wg_int wg_set_double_field(void* db, void* record, wg_int fieldnr, double data);
wg_int wg_set_str_field(void* db, void* record, wg_int fieldnr, char* data);

wg_int wg_get_field(void* db, void* record, wg_int fieldnr);      // returns 0 when error
wg_int wg_get_field_type(void* db, void* record, wg_int fieldnr); // returns 0 when error


/* ---------- general operations on encoded data -------- */

wg_int wg_get_encoded_type(void* db, wg_int data);
char* wg_get_type_name(void* db, wg_int type);
wg_int wg_free_encoded(void* db, wg_int data);

/* -------- encoding and decoding data: records contain encoded data only ---------- */


// null

wg_int wg_encode_null(void* db, wg_int data);
wg_int wg_decode_null(void* db, wg_int data);

// int

wg_int wg_encode_int(void* db, wg_int data);
wg_int wg_decode_int(void* db, wg_int data);

// double

wg_int wg_encode_double(void* db, double data);
double wg_decode_double(void* db, wg_int data);

// str (standard C string: zero-terminated array of chars)
// along with optional attached language indicator str

wg_int wg_encode_str(void* db, char* str, char* lang); ///< let lang==NULL if not used

char* wg_decode_str(void* db, wg_int data);
char* wg_decode_str_lang(void* db, wg_int data);

wg_int wg_decode_str_len(void* db, wg_int data); 
wg_int wg_decode_str_lang_len(void* db, wg_int data); 
wg_int wg_decode_str_copy(void* db, wg_int data, char* strbuf, wg_int buflen);
wg_int wg_decode_str_lang_copy(void* db, wg_int data, char* langbuf, wg_int buflen);                         

// xmlliteral (standard C string: zero-terminated array of chars)
// along with obligatory attached xsd:type str

wg_int wg_encode_xmlliteral(void* db, char* str, char* xsdtype);
char* wg_decode_xmlliteral_copy(void* db, wg_int data);   
char* wg_decode_xmlliteral_xsdtype_copy(void* db, wg_int data); 

wg_int wg_decode_xmlliteral_len(void* db, wg_int data);
wg_int wg_decode_xmlliteral_xsdtype_len(void* db, wg_int data);
wg_int wg_decode_xmlliteral(void* db, wg_int data, char* strbuf, wg_int buflen);                           
wg_int wg_decode_xmlliteral_xsdtype(void* db, wg_int data, char* strbuf, wg_int buflen);                                                 

// uri (standard C string: zero-terminated array of chars)
// along with an optional namespace str

wg_int wg_encode_uri(void* db, char* str, char* nspace); ///< let nspace==NULL if not used
char* wg_decode_uri_copy(void* db, wg_int data);
char* wg_decode_uri_namespace_copy(void* db, wg_int data);

wg_int wg_decode_uri_len(void* db, wg_int data); 
wg_int wg_decode_uri_namespace_len(void* db, wg_int data); 
wg_int wg_decode_uri(void* db, wg_int data, char* strbuf, wg_int buflen);
wg_int wg_decode_uri_namespace(void* db, wg_int data, char* nspacebuf, wg_int buflen);   

// blob (binary large object, i.e. any kind of data)
// along with an obligatory length in bytes
                                
wg_int wg_encode_blob(void* db, char* blob, wg_int bloblen);
wg_int wg_decode_blob_len(void* db, wg_int data);
wg_int wg_decode_blob(void* db, wg_int data, char* blobbuf, wg_int buflen);                                
char* wg_decode_blob_copy(void* db, wg_int data);

/// ptr to record

wg_int wg_encode_record(void* db, void* data);
void* wg_decode_record(void* db, wg_int data);



// ================ api part ends ================

#define CHECK
//#undef CHECK
#define RECORD_HEADER_GINTS 1
#define LITTLEENDIAN 1  ///< (intel is little-endian) difference in encoding tinystr
#define USETINYSTR 1    ///< undef to prohibit usage of tinystr

// recognising gint types as gb types: bits, shifts, masks

/*
special value null (unassigned)         integer 0

Pointers to word-len ints end with            ?01  = not eq
Pointers to data records end with             000  = not eq
Pointers to long string records end with      100  = eq
Pointers to doubleword-len doubles end with   010  = not eq
Pointers to 32byte string records end with    110  = not eq


Immediate integers end with                   011  = is eq

(Other immediates                             111 (continued below))
Immediate vars end with                      0111  
Immediate short floats                  0000 1111  = is eq
Immediate chars                         0001 1111  = is eq
Immediate dates                         0010 1111  = is eq
Immediate times                         0011 1111  = is eq
// Immediate tiny strings                  0100 1111  = is eq
Immediate anon constants                0101 1111  = is eq
*/


/* --- encoding and decoding basic data ---- */

#define SMALLINTBITS    0x3       ///< int ends with       011
#define SMALLINTSHFT  3
#define SMALLINTMASK  0x7

#define fits_smallint(i)   ((((i)<<SMALLINTSHFT)>>SMALLINTSHFT)==i)
#define encode_smallint(i) (((i)<<SMALLINTSHFT)|SMALLINTBITS)
#define decode_smallint(i) ((i)>>SMALLINTSHFT)

#define FULLINTBITS  0x1      ///< full int ptr ends with       01
#define FULLINTBITSV0  0x1    ///< full int type as 3-bit nr version 0:  001
#define FULLINTBITSV1  0x5    ///< full int type as 3-bit nr version 1:  101
#define FULLINTMASK  0x3

#define encode_fullint_offset(i) ((i)|FULLINTBITS)
#define decode_fullint_offset(i) ((i) & ~FULLINTMASK)

#define DATARECBITS  0x0      ///< datarec ptr ends with       000
#define DATARECMASK  0x7

#define encode_datarec_offset(i) (i)
#define decode_datarec_offset(i) (i)

#define LONGSTRBITS  0x4      ///< longstr ptr ends with       100
#define LONGSTRMASK  0x7

#define encode_longstr_offset(i) ((i)|LONGSTRBITS)
#define decode_longstr_offset(i) ((i) & ~LONGSTRMASK)

#define FULLDOUBLEBITS  0x2      ///< full double ptr ends with       010
#define FULLDOUBLEMASK  0x7

#define encode_fulldouble_offset(i) ((i)|FULLDOUBLEBITS)
#define decode_fulldouble_offset(i) ((i) & ~FULLDOUBLEMASK)

#define SHORTSTRBITS  0x6      ///< short str ptr ends with  110
#define SHORTSTRMASK  0x7

#define encode_shortstr_offset(i) ((i)|SHORTSTRBITS)
#define decode_shortstr_offset(i) ((i) & ~SHORTSTRMASK)


/* --- encoding and decoding other data ---- */

#define VARMASK  0xf
#define VARSHFT  4
#define VARBITS  0x7       ///< var ends with 0111

#define encode_var(i) (((i)<<VARSHFT)|VARBITS)
#define decode_var(i) ((i)>>VARSHFT)

#define CHARMASK  0xff
#define CHARSHFT  8
#define CHARBITS  0x1f       ///< char ends with 0001 1111

#define encode_char(i) (((i)<<CHARSHFT)|CHARBITS)
#define decode_char(i) ((i)>>CHARSHFT)

#define DATEMASK  0xff
#define DATESHFT  8
#define DATEBITS  0x2f       ///< date ends with 0010 1111

#define encode_date(i) (((i)<<DATESHFT)|DATEBITS)
#define decode_date(i) ((i)>>DATESHFT)

#define TIMEMASK  0xff
#define TIMESHFT  8
#define TIMEBITS  0x3f       ///< time ends with 0011 1111

#define encode_time(i) (((i)<<TIMESHFT)|TIMEBITS)
#define decode_time(i) ((i)>>TIMESHFT)

#define TINYSTRMASK  0xff
#define TINYSTRSHFT  8
#define TINYSTRBITS  0x4f       ///< tiny str ends with 0100 1111

#define ANONCONSTMASK  0xff
#define ANONCONSTSHFT  8
#define ANONCONSTBITS  0x5f       ///< anon const ends with 0101 1111

#define encode_anonconst(i) (((i)<<ANONCONSTSHFT)|ANONCONSTBITS)
#define decode_anonconst(i) ((i)>>ANONCONSTSHFT)

/* --- recognizing data ---- */

#define NORMALPTRMASK 0x7  ///< all pointers except fullint
#define NONPTRBITS 0x3
#define LASTFOURBITSMASK 0xf
#define PRELASTFOURBITSMASK 0xf0
#define LASTBYTEMASK 0xff

#define isptr(i)        ((i) && (((i)&NONPTRBITS)!=NONPTRBITS))

#define isdatarec(i)    (((i)&DATARECMASK)==DATARECBITS)
#define isfullint(i)    (((i)&FULLINTMASK)==FULLINTBITS)
#define isfulldouble(i) (((i)&FULLDOUBLEMASK)==FULLDOUBLEBITS)
#define isshortstr(i)   (((i)&SHORTSTRMASK)==SHORTSTRBITS)
#define islongstr(i)    (((i)&LONGSTRMASK)==LONGSTRBITS)

#define issmallint(i)   (((i)&SMALLINTMASK)==SMALLINTBITS)

#define isvar(i)   (((i)&VARMASK)==VARBITS)
#define ischar(i)   (((i)&CHARMASK)==CHARBITS)
#define isdate(i)   (((i)&DATEMASK)==DATEBITS)
#define istime(i)   (((i)&TIMEMASK)==TIMEBITS)
#define istinystr(i)   (((i)&TINYSTRMASK)==TINYSTRBITS)
#define isanonconst(i)   (((i)&ANONCONSTMASK)==ANONCONSTBITS)

/* ------ metainfo and special data items --------- */

#define datarec_size_bytes(i) (getusedobjectwantedbytes(i))
#define datarec_end_ptr(i) 


/* --------- record and longstr data object structure ---------- */


/* record data object

gint usage from start:

0:  encodes length in bytes. length is aligned to sizeof gint
1:  pointer to next sibling
2:  pointer to prev sibling or parent 
3:  data gints
...



---- conventional database rec ----------

car1:
id: 10
model: ford
licenceplate: 123LGH
owner: 20 (we will have ptr to rec 20)

car2:
id: 11
model: opel
licenceplate: 456RMH
owner: 20 (we will have ptr to rec 20)

person1:
parents: list of pointers to person1?
id: 20
fname: John
lname: Brown


---- xml node -------

<person fname="john" lname="brown">
  <owns>
    <car model="ford">
  </owns>
  <owns>  
    <car model="opel">
  </owns>
</person>

xml-corresponding rdf triplets

_10 model ford
_10 licenceplate 123LGH

_11 model opel
_11 licenceplate 456RMH

_20 fname john
_20 lname brown
_20 owns _10
_20 owns _11


(?x fname john) & (?x lname brown) & (?x owns ?y) & (?y model ford) => answer(?y)

solution: 

- locate from value index brown
- instantiate ?x with _20 
- scan _20 value occurrences with pred lname to find john
- scan _20 subject occurrences with pred owns to find _10
- scan _10 subject occurrences with pred model to find ford

----normal rdf triplets -----

_10 model ford
_10 licenceplate 123LGH
_10 owner _20

_11 model opel
_11 licenceplate 456RMH
_11 owner _20

_20 fname john
_20 lname brown


(?x fname john) & (?x lname brown) & (?y owner ?x) & (?y model ford) => answer(?y)

solution: 

- locate from value index brown
- instantiate ?x with _20 
- scan _20 value occurrences with pred lname to find john
- scan _20 value occurrences with pred owner to find _10
- scan _10 subject occurrences with pred model to find ford

--------- fromptr structure -------


fld 1 pts to either directly (single) occurrence or rec of occurrences:

single occ case:

- last bit zero indicates direct ptr to rec
- two previous bits indicate position in rec (0-3)

multiple (or far pos) case:

- last bit 1 indicates special pos list array ptr:

pos array:

recsize
position fld nr,
ptr to (single) rec or to corresp list of recs
position fld nr,
ptr to (single) rec or to corresp list o recs
...

where corresp list is made of pairs (list cells):

ptr to rec
ptr to next list cell

alternative:

ptr to rec
ptr to rec
ptr to rec
ptr to rec
ptr to next block


*/

/* record data object

gint usage from start:

0: encodes data obj length in bytes. length is aligned to sizeof gint
1: metainfo, incl object type:
   - last byte object type
   - top-level/dependent bit
   - original/derived bit
2: backlinks
3: actual gints ....
...


*/



/* longstr/xmlliteral/uri/blob data object

gint usage from start:

0:  encodes data obj length in bytes. length is aligned to sizeof gint
1:  metainfo, incl object type (longstr/xmlliteral/uri/blob/datarec etc):
    - last byte object type
    - byte before last: nr to delete from obj length to get real actual-bytes length
2:  refcount
3:  backlinks
4:  pointer to next longstr in the hash bucket, 0 if no following    
5:  lang/xsdtype/namespace str (offset):  if 0 not present
6:  actual bytes ....
...


*/


#define LONGSTR_HEADER_GINTS 6 /** including obj length gint */

#define LONGSTR_META_POS 1 /** metainfo, incl object type (longstr/xmlliteral/uri/blob/datarec etc) 
   last byte (low 0) object type (WG_STRTYPE,WG_XMLLITERALTYPE, etc)
   byte before last (low 1): 
         lendif: nr to delete from obj length to get real actual-bytes length of str
   low 2: unused
   low 3: unused
  */  
#define LONGSTR_META_LENDIFMASK 0xFF00 /** second lowest bytes contains lendif*/  
#define LONGSTR_META_LENDIFSHFT 8 /** shift 8 bits right to get lendif */
#define LONGSTR_META_TYPEMASK  0xFF /*** lowest byte contains actual subtype: str,uri,xmllliteral */
#define LONGSTR_REFCOUNT_POS 2 /**  reference count, if 0, delete*/
#define LONGSTR_BACKLINKS_POS 3 /**   backlinks structure offset */
#define LONGSTR_HASHCHAIN_POS 4 /**  offset of next longstr in the hash bucket, 0 if no following */
#define LONGSTR_EXTRASTR_POS 5 /**  lang/xsdtype/namespace str (encoded offset):  if 0 not present */


/* --------- error handling ------------ */

#define recordcheck(db,record,fieldnr,opname) { \
  if (!dbcheck(db)) {\
    show_data_error_str(db,"wrong database pointer given to ",opname);\
    return -1;\
  }\
  if (fieldnr<0 || getusedobjectwantedgintsnr(*((gint*)record))<=fieldnr+RECORD_HEADER_GINTS) {\
    show_data_error_str(db,"wrong field number given to ",opname);\
    return -2;\
  }\
}


/* ==== Protos ==== */

//void free_field_data(void* db,gint fielddata, gint fromrecoffset, gint fromrecfield);
gint free_field_encoffset(void* db,gint encoffset, gint fromrecoffset, gint fromrecfield);

gint find_create_longstr(void* db, char* data, char* extrastr, gint type, gint length);

gint show_data_error(void* db, char* errmsg);
gint show_data_error_nr(void* db, char* errmsg, gint nr);
gint show_data_error_double(void* db, char* errmsg, double nr);
gint show_data_error_str(void* db, char* errmsg, char* str);

#endif