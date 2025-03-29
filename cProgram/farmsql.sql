-- MySQL 테이블 생성을 위한 간소화된 쿼리문
-- 데이터베이스 생성 (없는 경우)
SELECT user, host FROM mysql.user WHERE user = 'myuser';

CREATE DATABASE IF NOT EXISTS smartfarm_db;
grant all privileges on smartfarm_db.* to 'myuser'@'%';
-- 데이터베이스 선택
USE smartfarm_db;
CREATE TABLE IF NOT EXISTS data_records (
    RecordTime DATETIME NOT NULL DEFAULT (current_time) PRIMARY KEY,
    Temperature INT NOT NULL,
    Humidity INT NOT NULL,
    SoilMoisture INT NOT NULL,
    Sunshine INT NOT NULL,
    Cond VARCHAR(20) NOT NULL
);

SELECT
    DATE_FORMAT(RecordTime, '%Y-%m-%d %H:%i:%s') AS RecordTime,
    Temperature, Humidity, SoilMoisture, Sunshine, Cond
FROM smartfarm_db.data_records
WHERE RecordTime > '2025-03-29'
ORDER BY RecordTime DESC;

-- 샘플 데이터 삽입 (테스트용)
use smartfarm_db;
INSERT INTO data_records (Temperature, Humidity, SoilMoisture, Sunshine, cond)
VALUES (20, 30, 52, 46, 'good');
use smartfarm_db;
INSERT INTO data_records (Temperature, Humidity, SoilMoisture, Sunshine, cond)
VALUES (13, 15, 12, 5, 'good');

USE smartfarm_db;
INSERT INTO data_records (Temperature, Humidity, SoilMoisture, Sunshine, Cond) VALUES (20, 21, 53, 50, 'good');

use smartfarm_db;
DELETE FROM data_records;
