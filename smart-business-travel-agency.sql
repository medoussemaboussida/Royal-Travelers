/*==============================================================*/
/* DBMS name:      ORACLE Version 11g                           */
/* Created on:     04/11/2022 17:48:22                          */
/*==============================================================*/


/*==============================================================*/
/* Table: CLIENT                                                */
/*==============================================================*/
create table CLIENT 
(
   CIN_C                INTEGER              not null,
   NOM_C                VARCHAR2(20)         not null,
   PRENOM_C             VARCHAR2(20)         not null,
   AGE_C                INTEGER              not null,
   EMAIL_C              VARCHAR2(25)         not null,
   PHONE_C              VARCHAR2(12)         not null,
   BUDGET_C             FLOAT(5)             not null,
   PTS_FIDELITE_C       INTEGER
);

alter table CLIENT
   add constraint PK_CLIENT primary key (CIN_C);

/*==============================================================*/
/* Table: EMPOLYE                                               */
/*==============================================================*/
create table EMPOLYE 
(
   CIN_E                INTEGER              not null,
   NOM_E                VARCHAR2(20)         not null,
   PRENOM_E             VARCHAR2(20)         not null,
   EMAIL_E              VARCHAR2(25)         not null,
   PHONE_E              VARCHAR2(12)         not null,
   FONCTION_E           VARCHAR2(20)         not null,
   MDP                  CLOB                 not null
);

alter table EMPOLYE
   add constraint PK_EMPOLYE primary key (CIN_E);

/*==============================================================*/
/* Table: GERER                                                 */
/*==============================================================*/
create table GERER 
(
   CIN_E                INTEGER              not null,
   ID_MISSION           INTEGER              not null
);

alter table GERER
   add constraint PK_GERER primary key (CIN_E, ID_MISSION);

/*==============================================================*/
/* Table: LOGEMENT                                              */
/*==============================================================*/
create table LOGEMENT 
(
   ID_LOG               INTEGER              not null,
   TYPE_LOG             VARCHAR2(20)         not null,
   DUREE_LOG            VARCHAR2(20)         not null,
   PRIX_LOG             FLOAT(5)             not null,
   LIEU                 CHAR(20)             not null
);

alter table LOGEMENT
   add constraint PK_LOGEMENT primary key (ID_LOG);

/*==============================================================*/
/* Table: MISSION                                               */
/*==============================================================*/
create table MISSION 
(
   ID_MISSION           INTEGER              not null,
   ID_LOG               INTEGER              not null,
   ID_TRAN              INTEGER              not null,
   CIN_C                INTEGER              not null,
   DATE_DEPART          DATE                 not null,
   DATE_RETOUR          DATE                 not null,
   TYPE_MISSION         VARCHAR2(20)         not null,
   DIRECTION            CHAR(20)             not null
);

alter table MISSION
   add constraint PK_MISSION primary key (ID_MISSION);

/*==============================================================*/
/* Table: MOYEN_DE_TRANSPORT                                    */
/*==============================================================*/
create table MOYEN_DE_TRANSPORT 
(
   ID_TRAN              INTEGER              not null,
   TYPE                 CHAR(20)             not null,
   PRIX                 FLOAT(5)             not null,
   NB_MOY               INTEGER              not null
);

alter table MOYEN_DE_TRANSPORT
   add constraint PK_MOYEN_DE_TRANSPORT primary key (ID_TRAN);

alter table GERER
   add constraint FK_GERER_GERER_EMPOLYE foreign key (CIN_E)
      references EMPOLYE (CIN_E);

alter table GERER
   add constraint FK_GERER_GERER2_MISSION foreign key (ID_MISSION)
      references MISSION (ID_MISSION);

alter table MISSION
   add constraint FK_MISSION_DEMANDER_CLIENT foreign key (CIN_C)
      references CLIENT (CIN_C);

alter table MISSION
   add constraint FK_MISSION_RESERVER_LOGEMENT foreign key (ID_LOG)
      references LOGEMENT (ID_LOG);

alter table MISSION
   add constraint FK_MISSION_TRANSPORT_MOYEN_DE foreign key (ID_TRAN)
      references MOYEN_DE_TRANSPORT (ID_TRAN);

