// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#ifndef ANNOTATOR_ANNOTATORLIB_PROJECT_H
#define ANNOTATOR_ANNOTATORLIB_PROJECT_H

/************************************************************
 Project class header
 ************************************************************/

#include <string>

#include <chrono>
#include <ctime>

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <AnnotatorLib/ImageSet.h>
#include <AnnotatorLib/Session.h>

namespace AnnotatorLib {

namespace Storage {
class AbstractStorage;
}

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API Project {

public:

  /**
   * @brief create
   * @param name
   * @param imageSetType
   * @param imageSetPath
   * @param storageType
   * @param storagePath
   * @return
   */
  static Project *create(std::string name, ImageSetType imageSetType,
                         std::string imageSetPath, StorageType storageType,
                         std::string storagePath);

  /**
   * @brief create
   * @param name
   * @param imageSetType
   * @param imageSetPath
   * @param storageType
   * @param storagePath
   * @return
   */
  static Project *create(std::string name, std::string imageSetType,
                         std::string imageSetPath, std::string storageType,
                         std::string storagePath);

  /**
   *
   * @param path
   * @return project
   */
  static Project *load(std::string path);

  ///////////////////////////////////////////////

  ~Project();

  Session *getSession() const;

  AnnotatorLib::Storage::AbstractStorage *getStorage() const;

  std::string getName() const;

  /**
   * @brief Get the total spended time of this project in seconds.
   * @return
   */
  unsigned long getDuration();

  ImageSet *getImageSet() const;

  /**
   * @brief load
   */
  void load();

  /**
   *
   * @param project
   * @param path
   */
  static void save(Project *project, std::string path);

  /**
   * @brief save
   */
  void save();

  /**
   * @brief equals
   * @param other
   * @return
   */
  bool equals(Project *other) const;
  /**
   * @brief getImageSetPath
   * @return
   */
  std::string getImageSetPath() const;
  /**
   * @brief setPath
   * @param path
   */
  void setPath(std::string path);

  /**
   * @brief getPath
   * @return
   */
  std::string getPath() const;

  void setActive(bool b);

  bool isActive() const;

 protected:

  Project();

  Project(std::string name, ImageSetType imageSetType, std::string imageSetPath,
          StorageType storageType, std::string storagePath);

  /**
   * @brief loadSession
   */
  void loadSession();

  void loadImageSet(QDomElement &root, ImageSetType &type,
                    std::string &imageSetPath);

  void loadStorage(QDomElement &root, StorageType &type,
                   std::string &storagePath);

  void loadRoot(QDomDocument &doc, QDomElement &root, std::string &name);

  void loadProjectStatistics(QDomElement &root);

  /**
   * @brief saveSession
   */
  void saveSession();

  QDomElement saveImageSet(QDomDocument &doc);

  QDomElement saveStorage(QDomDocument &doc);

  QDomElement saveRoot(QDomDocument &doc);

  QDomElement saveProjectStatistics(QDomDocument &doc);

  ///////////////////////////////////////////////

  std::string name = "";

  std::string path = "";

  unsigned long total_duration_sec = 0;

  ImageSetType imageSetType = ImageSetType::UNKNOWN;

  ImageSet *imageSet = nullptr;

  StorageType storageType = StorageType::UNKNOWN;

  std::string storagePath = "";

  Session *session = nullptr;

  std::chrono::time_point<std::chrono::system_clock> time_point_start;

  bool active = true;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of Project class header
 ************************************************************/

#endif
